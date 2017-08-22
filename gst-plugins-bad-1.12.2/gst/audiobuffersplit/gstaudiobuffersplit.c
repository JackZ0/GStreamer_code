/*
 * GStreamer
 * Copyright (C) 2016 Sebastian Dröge <sebastian@centricular.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gstaudiobuffersplit.h"

#define GST_CAT_DEFAULT gst_audio_buffer_split_debug
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/x-raw")
    );

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("audio/x-raw")
    );

enum
{
  PROP_0,
  PROP_OUTPUT_BUFFER_DURATION,
  PROP_ALIGNMENT_THRESHOLD,
  PROP_DISCONT_WAIT,
  PROP_STRICT_BUFFER_SIZE,
  LAST_PROP
};

#define DEFAULT_OUTPUT_BUFFER_DURATION_N (1)
#define DEFAULT_OUTPUT_BUFFER_DURATION_D (50)
#define DEFAULT_ALIGNMENT_THRESHOLD   (40 * GST_MSECOND)
#define DEFAULT_DISCONT_WAIT (1 * GST_SECOND)
#define DEFAULT_STRICT_BUFFER_SIZE (FALSE)

#define parent_class gst_audio_buffer_split_parent_class
G_DEFINE_TYPE (GstAudioBufferSplit, gst_audio_buffer_split, GST_TYPE_ELEMENT);

static GstFlowReturn gst_audio_buffer_split_sink_chain (GstPad * pad,
    GstObject * parent, GstBuffer * buffer);
static gboolean gst_audio_buffer_split_sink_event (GstPad * pad,
    GstObject * parent, GstEvent * event);
static gboolean gst_audio_buffer_split_src_query (GstPad * pad,
    GstObject * parent, GstQuery * query);

static void gst_audio_buffer_split_finalize (GObject * object);
static void gst_audio_buffer_split_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_audio_buffer_split_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);

static GstStateChangeReturn gst_audio_buffer_split_change_state (GstElement *
    element, GstStateChange transition);

static void
gst_audio_buffer_split_class_init (GstAudioBufferSplitClass * klass)
{
  GObjectClass *gobject_class = (GObjectClass *) klass;
  GstElementClass *gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_audio_buffer_split_set_property;
  gobject_class->get_property = gst_audio_buffer_split_get_property;
  gobject_class->finalize = gst_audio_buffer_split_finalize;

  g_object_class_install_property (gobject_class, PROP_OUTPUT_BUFFER_DURATION,
      gst_param_spec_fraction ("output-buffer-duration",
          "Output Buffer Duration", "Output block size in seconds", 1, G_MAXINT,
          G_MAXINT, 1, DEFAULT_OUTPUT_BUFFER_DURATION_N,
          DEFAULT_OUTPUT_BUFFER_DURATION_D,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS |
          GST_PARAM_MUTABLE_READY));

  g_object_class_install_property (gobject_class, PROP_ALIGNMENT_THRESHOLD,
      g_param_spec_uint64 ("alignment-threshold", "Alignment Threshold",
          "Timestamp alignment threshold in nanoseconds", 0,
          G_MAXUINT64 - 1, DEFAULT_ALIGNMENT_THRESHOLD,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS |
          GST_PARAM_MUTABLE_READY));

  g_object_class_install_property (gobject_class, PROP_DISCONT_WAIT,
      g_param_spec_uint64 ("discont-wait", "Discont Wait",
          "Window of time in nanoseconds to wait before "
          "creating a discontinuity", 0,
          G_MAXUINT64 - 1, DEFAULT_DISCONT_WAIT,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS |
          GST_PARAM_MUTABLE_READY));

  g_object_class_install_property (gobject_class, PROP_STRICT_BUFFER_SIZE,
      g_param_spec_boolean ("strict-buffer-size", "Strict buffer size",
          "Discard the last samples at EOS or discont if they are too "
          "small to fill a buffer", DEFAULT_STRICT_BUFFER_SIZE,
          G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS |
          GST_PARAM_MUTABLE_READY));

  gst_element_class_set_static_metadata (gstelement_class,
      "Audio Buffer Split", "Audio/Filter",
      "Splits raw audio buffers into equal sized chunks",
      "Sebastian Dröge <sebastian@centricular.com>");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_template));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_template));

  gstelement_class->change_state = gst_audio_buffer_split_change_state;
}

static void
gst_audio_buffer_split_init (GstAudioBufferSplit * self)
{
  self->sinkpad = gst_pad_new_from_static_template (&sink_template, "sink");
  gst_pad_set_chain_function (self->sinkpad,
      GST_DEBUG_FUNCPTR (gst_audio_buffer_split_sink_chain));
  gst_pad_set_event_function (self->sinkpad,
      GST_DEBUG_FUNCPTR (gst_audio_buffer_split_sink_event));
  GST_PAD_SET_PROXY_CAPS (self->sinkpad);
  gst_element_add_pad (GST_ELEMENT (self), self->sinkpad);

  self->srcpad = gst_pad_new_from_static_template (&src_template, "src");
  gst_pad_set_query_function (self->srcpad,
      GST_DEBUG_FUNCPTR (gst_audio_buffer_split_src_query));
  GST_PAD_SET_PROXY_CAPS (self->srcpad);
  gst_pad_use_fixed_caps (self->srcpad);
  gst_element_add_pad (GST_ELEMENT (self), self->srcpad);

  self->output_buffer_duration_n = DEFAULT_OUTPUT_BUFFER_DURATION_N;
  self->output_buffer_duration_d = DEFAULT_OUTPUT_BUFFER_DURATION_D;
  self->alignment_threshold = DEFAULT_ALIGNMENT_THRESHOLD;
  self->discont_wait = DEFAULT_DISCONT_WAIT;
  self->strict_buffer_size = DEFAULT_STRICT_BUFFER_SIZE;

  self->adapter = gst_adapter_new ();
}

static void
gst_audio_buffer_split_finalize (GObject * object)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (object);

  if (self->adapter) {
    gst_object_unref (self->adapter);
    self->adapter = NULL;
  }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

static void
gst_audio_buffer_split_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (object);

  switch (property_id) {
    case PROP_OUTPUT_BUFFER_DURATION:
      self->output_buffer_duration_n = gst_value_get_fraction_numerator (value);
      self->output_buffer_duration_d =
          gst_value_get_fraction_denominator (value);
      break;
    case PROP_ALIGNMENT_THRESHOLD:
      self->alignment_threshold = g_value_get_uint64 (value);
      break;
    case PROP_DISCONT_WAIT:
      self->discont_wait = g_value_get_uint64 (value);
      break;
    case PROP_STRICT_BUFFER_SIZE:
      self->strict_buffer_size = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static void
gst_audio_buffer_split_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (object);

  switch (property_id) {
    case PROP_OUTPUT_BUFFER_DURATION:
      gst_value_set_fraction (value, self->output_buffer_duration_n,
          self->output_buffer_duration_d);
      break;
    case PROP_ALIGNMENT_THRESHOLD:
      g_value_set_uint64 (value, self->alignment_threshold);
      break;
    case PROP_DISCONT_WAIT:
      g_value_set_uint64 (value, self->discont_wait);
      break;
    case PROP_STRICT_BUFFER_SIZE:
      g_value_set_boolean (value, self->strict_buffer_size);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static GstStateChangeReturn
gst_audio_buffer_split_change_state (GstElement * element,
    GstStateChange transition)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (element);
  GstStateChangeReturn state_ret;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      gst_audio_info_init (&self->info);
      gst_segment_init (&self->segment, GST_FORMAT_TIME);
      self->discont_time = GST_CLOCK_TIME_NONE;
      self->next_offset = -1;
      self->resync_time = GST_CLOCK_TIME_NONE;
      self->current_offset = -1;
      self->accumulated_error = 0;
      self->samples_per_buffer = 0;
      break;
    default:
      break;
  }

  state_ret =
      GST_ELEMENT_CLASS (gst_audio_buffer_split_parent_class)->change_state
      (element, transition);
  if (state_ret == GST_STATE_CHANGE_FAILURE)
    return state_ret;

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      gst_adapter_clear (self->adapter);
      break;
    default:
      break;
  }

  return state_ret;
}

static GstFlowReturn
gst_audio_buffer_split_output (GstAudioBufferSplit * self, gboolean force)
{
  gint rate, bpf;
  gint size, avail;
  GstFlowReturn ret = GST_FLOW_OK;

  rate = GST_AUDIO_INFO_RATE (&self->info);
  bpf = GST_AUDIO_INFO_BPF (&self->info);

  if (self->samples_per_buffer == 0)
    return GST_FLOW_NOT_NEGOTIATED;

  size = self->samples_per_buffer * bpf;

  /* If we accumulated enough error for one sample, include one
   * more sample in this buffer. Accumulated error is updated below */
  if (self->error_per_buffer + self->accumulated_error >=
      self->output_buffer_duration_d)
    size += bpf;

  while ((avail = gst_adapter_available (self->adapter)) >= size || (force
          && avail > 0)) {
    GstBuffer *buffer;
    GstClockTime resync_time_diff;

    size = MIN (size, avail);
    buffer = gst_adapter_take_buffer (self->adapter, size);

    resync_time_diff =
        gst_util_uint64_scale (self->current_offset, GST_SECOND, rate);
    if (self->segment.rate < 0.0) {
      if (self->resync_time > resync_time_diff)
        GST_BUFFER_TIMESTAMP (buffer) = self->resync_time - resync_time_diff;
      else
        GST_BUFFER_TIMESTAMP (buffer) = 0;
      GST_BUFFER_DURATION (buffer) =
          gst_util_uint64_scale (size / bpf, GST_SECOND, rate);

      self->current_offset += size / bpf;
    } else {
      GST_BUFFER_TIMESTAMP (buffer) = self->resync_time + resync_time_diff;
      self->current_offset += size / bpf;
      resync_time_diff =
          gst_util_uint64_scale (self->current_offset, GST_SECOND, rate);
      GST_BUFFER_DURATION (buffer) =
          resync_time_diff - (GST_BUFFER_TIMESTAMP (buffer) -
          self->resync_time);
    }

    GST_BUFFER_OFFSET (buffer) = GST_BUFFER_OFFSET_NONE;
    GST_BUFFER_OFFSET_END (buffer) = GST_BUFFER_OFFSET_NONE;

    self->accumulated_error =
        (self->accumulated_error +
        self->error_per_buffer) % self->output_buffer_duration_d;

    GST_LOG_OBJECT (self,
        "Outputting buffer at timestamp %" GST_TIME_FORMAT " with duration %"
        GST_TIME_FORMAT " (%u samples)",
        GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buffer)),
        GST_TIME_ARGS (GST_BUFFER_DURATION (buffer)), size / bpf);

    ret = gst_pad_push (self->srcpad, buffer);
    if (ret != GST_FLOW_OK)
      break;
  }

  return ret;
}

static GstFlowReturn
gst_audio_buffer_split_handle_discont (GstAudioBufferSplit * self,
    GstBuffer * buffer)
{
  GstClockTime timestamp;
  gsize size;
  guint64 start_offset, end_offset;
  gint rate, bpf;
  gboolean discont = FALSE;
  GstFlowReturn ret = GST_FLOW_OK;

  timestamp = GST_BUFFER_TIMESTAMP (buffer);

  rate = GST_AUDIO_INFO_RATE (&self->info);
  bpf = GST_AUDIO_INFO_BPF (&self->info);
  start_offset = gst_util_uint64_scale (timestamp, rate, GST_SECOND);
  size = gst_buffer_get_size (buffer);
  end_offset = start_offset + size / bpf;

  if (self->segment.rate < 0.0) {
    guint64 tmp = end_offset;
    end_offset = start_offset;
    start_offset = tmp;
  }

  if (GST_BUFFER_IS_DISCONT (buffer)
      || GST_BUFFER_FLAG_IS_SET (buffer, GST_BUFFER_FLAG_RESYNC)
      || self->resync_time == GST_CLOCK_TIME_NONE) {
    discont = TRUE;
  } else {
    guint64 diff, max_sample_diff;

    /* Check discont, based on audiobasesink */
    if (start_offset <= self->next_offset)
      diff = self->next_offset - start_offset;
    else
      diff = start_offset - self->next_offset;

    max_sample_diff =
        gst_util_uint64_scale_int (self->alignment_threshold, rate, GST_SECOND);

    /* Discont! */
    if (G_UNLIKELY (diff >= max_sample_diff)) {
      if (self->discont_wait > 0) {
        if (self->discont_time == GST_CLOCK_TIME_NONE) {
          self->discont_time = timestamp;
        } else if (timestamp - self->discont_time >= self->discont_wait) {
          discont = TRUE;
          self->discont_time = GST_CLOCK_TIME_NONE;
        }
      } else {
        discont = TRUE;
      }
    } else if (G_UNLIKELY (self->discont_time != GST_CLOCK_TIME_NONE)) {
      /* we have had a discont, but are now back on track! */
      self->discont_time = GST_CLOCK_TIME_NONE;
    }
  }

  if (discont) {
    /* Have discont, need resync */
    if (self->next_offset != -1) {
      GST_INFO_OBJECT (self, "Have discont. Expected %"
          G_GUINT64_FORMAT ", got %" G_GUINT64_FORMAT,
          self->next_offset, start_offset);
      if (self->strict_buffer_size) {
        gst_adapter_clear (self->adapter);
        ret = GST_FLOW_OK;
      } else {
        ret = gst_audio_buffer_split_output (self, TRUE);
      }
    }
    self->next_offset = end_offset;
    self->resync_time = timestamp;
    self->current_offset = 0;
    self->accumulated_error = 0;
    gst_adapter_clear (self->adapter);
  } else {
    if (self->segment.rate < 0.0) {
      if (self->next_offset > size / bpf)
        self->next_offset -= size / bpf;
      else
        self->next_offset = 0;
    } else {
      self->next_offset += size / bpf;
    }
  }

  return ret;
}

static GstBuffer *
gst_audio_buffer_split_clip_buffer (GstAudioBufferSplit * self,
    GstBuffer * buffer)
{
  return gst_audio_buffer_clip (buffer, &self->segment,
      GST_AUDIO_INFO_RATE (&self->info), GST_AUDIO_INFO_BPF (&self->info));
}

static GstFlowReturn
gst_audio_buffer_split_sink_chain (GstPad * pad, GstObject * parent,
    GstBuffer * buffer)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (parent);
  GstFlowReturn ret;

  if (GST_AUDIO_INFO_FORMAT (&self->info) == GST_AUDIO_FORMAT_UNKNOWN) {
    gst_buffer_unref (buffer);
    return GST_FLOW_NOT_NEGOTIATED;
  }

  buffer = gst_audio_buffer_split_clip_buffer (self, buffer);
  if (!buffer)
    return GST_FLOW_OK;

  ret = gst_audio_buffer_split_handle_discont (self, buffer);
  if (ret != GST_FLOW_OK) {
    gst_buffer_unref (buffer);
    return ret;
  }

  gst_adapter_push (self->adapter, buffer);

  return gst_audio_buffer_split_output (self, FALSE);
}

static gboolean
gst_audio_buffer_split_sink_event (GstPad * pad, GstObject * parent,
    GstEvent * event)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (parent);
  gboolean ret = FALSE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CAPS:{
      GstCaps *caps;

      gst_event_parse_caps (event, &caps);

      ret = gst_audio_info_from_caps (&self->info, caps);

      if (ret) {
        self->samples_per_buffer =
            (((guint64) GST_AUDIO_INFO_RATE (&self->info)) *
            self->output_buffer_duration_n) / self->output_buffer_duration_d;
        if (self->samples_per_buffer == 0)
          ret = FALSE;

        self->error_per_buffer =
            (((guint64) GST_AUDIO_INFO_RATE (&self->info)) *
            self->output_buffer_duration_n) % self->output_buffer_duration_d;
        self->accumulated_error = 0;

        GST_DEBUG_OBJECT (self, "Got caps %" GST_PTR_FORMAT, caps);
        GST_DEBUG_OBJECT (self, "Buffer duration: %u/%u",
            self->output_buffer_duration_n, self->output_buffer_duration_d);
        GST_DEBUG_OBJECT (self, "Samples per buffer: %u (error: %u/%u)",
            self->samples_per_buffer, self->error_per_buffer,
            self->output_buffer_duration_d);
      } else {
        ret = FALSE;
      }

      if (ret)
        ret = gst_pad_event_default (pad, parent, event);
      else
        gst_event_unref (event);

      break;
    }
    case GST_EVENT_FLUSH_STOP:
      gst_segment_init (&self->segment, GST_FORMAT_TIME);
      self->discont_time = GST_CLOCK_TIME_NONE;
      self->next_offset = -1;
      self->resync_time = GST_CLOCK_TIME_NONE;
      self->current_offset = -1;
      self->accumulated_error = 0;
      gst_adapter_clear (self->adapter);
      ret = gst_pad_event_default (pad, parent, event);
      break;
    case GST_EVENT_SEGMENT:
      gst_event_copy_segment (event, &self->segment);
      if (self->segment.format != GST_FORMAT_TIME) {
        gst_event_unref (event);
        ret = FALSE;
      } else {
        ret = gst_pad_event_default (pad, parent, event);
      }
      break;
    case GST_EVENT_EOS:
      if (self->strict_buffer_size)
        gst_adapter_clear (self->adapter);
      else
        gst_audio_buffer_split_output (self, TRUE);
      ret = gst_pad_event_default (pad, parent, event);
      break;
    default:
      ret = gst_pad_event_default (pad, parent, event);
      break;
  }

  return ret;
}

static gboolean
gst_audio_buffer_split_src_query (GstPad * pad,
    GstObject * parent, GstQuery * query)
{
  GstAudioBufferSplit *self = GST_AUDIO_BUFFER_SPLIT (parent);
  gboolean ret = FALSE;

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_LATENCY:{
      if ((ret = gst_pad_peer_query (self->sinkpad, query))) {
        GstClockTime latency;
        GstClockTime min, max;
        gboolean live;

        gst_query_parse_latency (query, &live, &min, &max);

        GST_DEBUG_OBJECT (self, "Peer latency: min %"
            GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
            GST_TIME_ARGS (min), GST_TIME_ARGS (max));

        latency =
            gst_util_uint64_scale (GST_SECOND, self->output_buffer_duration_n,
            self->output_buffer_duration_d);

        GST_DEBUG_OBJECT (self, "Our latency: min %" GST_TIME_FORMAT
            ", max %" GST_TIME_FORMAT,
            GST_TIME_ARGS (latency), GST_TIME_ARGS (latency));

        min += latency;
        if (max != GST_CLOCK_TIME_NONE)
          max += latency;

        GST_DEBUG_OBJECT (self, "Calculated total latency : min %"
            GST_TIME_FORMAT " max %" GST_TIME_FORMAT,
            GST_TIME_ARGS (min), GST_TIME_ARGS (max));

        gst_query_set_latency (query, live, min, max);
      }

      break;
    }
    default:
      ret = gst_pad_query_default (pad, parent, query);
      break;
  }

  return ret;
}

static gboolean
plugin_init (GstPlugin * plugin)
{
  GST_DEBUG_CATEGORY_INIT (gst_audio_buffer_split_debug, "audiobuffersplit",
      0, "Audio buffer splitter");

  gst_element_register (plugin, "audiobuffersplit", GST_RANK_NONE,
      GST_TYPE_AUDIO_BUFFER_SPLIT);

  return TRUE;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    audiobuffersplit,
    "Audio buffer splitter",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
