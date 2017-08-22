BEGIN {
S["am__EXEEXT_FALSE"]=""
S["am__EXEEXT_TRUE"]="#"
S["LTLIBOBJS"]=""
S["LIBOBJS"]=""
S["HAVE_LIBAV_UNINSTALLED_FALSE"]="#"
S["HAVE_LIBAV_UNINSTALLED_TRUE"]=""
S["WIN32_LIBS"]=""
S["SWSCALE_DEPS"]="$(top_builddir)/gst-libs/ext/libav/libswscale/libswscale.a                 $(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
S["LIBAV_SUBDIRS"]="gst-libs"
S["LIBAV_DEPS"]="$(top_builddir)/gst-libs/ext/libav/libavformat/libavformat.a               $(top_builddir)/gst-libs/ext/libav/libavcodec/libavcodec.a               "\
"$(top_builddir)/gst-libs/ext/libav/libavfilter/libavfilter.a               $(top_builddir)/gst-libs/ext/libav/libswresample/libswresample.a         "\
"      $(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
S["HAVE_LZMA_FALSE"]="#"
S["HAVE_LZMA_TRUE"]=""
S["HAVE_BZ2_FALSE"]="#"
S["HAVE_BZ2_TRUE"]=""
S["LIBAV_EXTERNALS_REVISION"]=""
S["LIBAV_REVISION"]=""
S["LIBAV_SVN"]=""
S["LIBAV_CO_DIR"]=""
S["SWSCALE_LIBS"]="$(top_builddir)/gst-libs/ext/libav/libswscale/libswscale.a                 $(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
S["SWSCALE_CFLAGS"]="-I $(top_srcdir)/gst-libs/ext/libav                   -I $(top_builddir)/gst-libs/ext/libav                   -Wno-deprecated-declarations"
S["LIBAV_LIBS"]="$(top_builddir)/gst-libs/ext/libav/libavformat/libavformat.a               $(top_builddir)/gst-libs/ext/libav/libavcodec/libavcodec.a               "\
"$(top_builddir)/gst-libs/ext/libav/libavfilter/libavfilter.a               $(top_builddir)/gst-libs/ext/libav/libswresample/libswresample.a         "\
"      $(top_builddir)/gst-libs/ext/libav/libavutil/libavutil.a"
S["LIBAV_CFLAGS"]="-I $(top_srcdir)/gst-libs/ext/libav                 -I $(top_builddir)/gst-libs/ext/libav                  -Wno-deprecated-declarations"
S["GST_LIBAV_ENABLE_GPL_FALSE"]=""
S["GST_LIBAV_ENABLE_GPL_TRUE"]="#"
S["DARWIN_LDFLAGS"]=""
S["GST_PLUGIN_LDFLAGS"]="-module -avoid-version -export-symbols-regex '^_*gst_plugin_.*' -no-undefined -Wl,-Bsymbolic-functions"
S["GST_ALL_LDFLAGS"]="-no-undefined -Wl,-Bsymbolic-functions"
S["GST_OPTION_CFLAGS"]="$(WARNING_CFLAGS) $(ERROR_CFLAGS) $(DEBUG_CFLAGS) $(PROFILE_CFLAGS) $(GCOV_CFLAGS) $(OPT_CFLAGS) $(DEPRECATED_CFLAGS)"
S["DEPRECATED_CFLAGS"]=""
S["PROFILE_CFLAGS"]=""
S["GST_LEVEL_DEFAULT"]="GST_LEVEL_NONE"
S["ERROR_CFLAGS"]=""
S["WARNING_CFLAGS"]=" -Wall -Wdeclaration-after-statement -Wvla -Wpointer-arith -Wmissing-declarations -Wmissing-prototypes -Wredundant-decls -Wundef -Wwrite-strings -Wf"\
"ormat-nonliteral -Wformat-security -Wold-style-definition -Winit-self -Wmissing-include-dirs -Waddress -Waggregate-return -Wno-multichar -Wnested-ex"\
"terns"
S["GST_PLUGIN_BUILD_STATIC_FALSE"]=""
S["GST_PLUGIN_BUILD_STATIC_TRUE"]="#"
S["GST_PLUGIN_LIBTOOLFLAGS"]="--tag=disable-static"
S["plugindir"]="$(libdir)/gstreamer-1.0"
S["PLUGINDIR"]="/home/installed/lib/gstreamer-1.0"
S["HAVE_GST_CHECK_FALSE"]="#"
S["HAVE_GST_CHECK_TRUE"]=""
S["GST_CHECK_LIBS"]="-L/home/installed/lib -lgstcheck-1.0 -lm -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
S["GST_CHECK_CFLAGS"]="-pthread -I/home/installed/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["GSTPB_PLUGINS_DIR"]="/home/installed/lib/gstreamer-1.0"
S["GST_PLUGINS_BASE_DIR"]="/home/installed/lib/gstreamer-1.0/gst:/home/installed/lib/gstreamer-1.0/sys:/home/installed/lib/gstreamer-1.0/ext"
S["GST_PLUGINS_BASE_LIBS"]="-L/home/installed/lib -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
S["GST_PLUGINS_BASE_CFLAGS"]="-pthread -I/home/installed/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["GST_BASE_LIBS"]="-L/home/installed/lib -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
S["GST_BASE_CFLAGS"]="-pthread -I/home/installed/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["GST_PLUGINS_DIR"]="/home/installed/lib/gstreamer-1.0"
S["GST_TOOLS_DIR"]="/home/installed/bin"
S["GST_LIBS"]="-L/home/installed/lib -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0"
S["GST_CFLAGS"]="-I$(top_srcdir)/gst-libs -I$(top_builddir)/gst-libs -pthread -I/home/installed/include/gstreamer-1.0 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux"\
"-gnu/glib-2.0/include  -DG_THREADS_MANDATORY -DG_DISABLE_CAST_CHECKS $(GST_OPTION_CFLAGS)"
S["GIO_LDFLAGS"]=""
S["GIO_LIBS"]="-lgio-2.0 -lgobject-2.0 -lglib-2.0"
S["GIO_CFLAGS"]="-pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["GLIB_EXTRA_CFLAGS"]=" -DG_THREADS_MANDATORY -DG_DISABLE_CAST_CHECKS"
S["GLIB_MKENUMS"]="glib-mkenums"
S["GLIB_GENMARSHAL"]="glib-genmarshal"
S["GLIB_LIBS"]="-lgobject-2.0 -lgmodule-2.0 -pthread -lglib-2.0"
S["GLIB_CFLAGS"]="-pthread -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["GLIB_REQ"]="2.40.0"
S["PTHREAD_CFLAGS"]="-pthread"
S["PTHREAD_LIBS"]=""
S["PTHREAD_CC"]="gcc"
S["ax_pthread_config"]=""
S["LIBM"]="-lm"
S["ENABLE_PLUGIN_DOCS_FALSE"]="#"
S["ENABLE_PLUGIN_DOCS_TRUE"]=""
S["pkgpyexecdir"]="${pyexecdir}/gst-libav"
S["pyexecdir"]="${exec_prefix}/lib/python2.7/site-packages"
S["pkgpythondir"]="${pythondir}/gst-libav"
S["pythondir"]="${prefix}/lib/python2.7/site-packages"
S["PYTHON_PLATFORM"]="linux2"
S["PYTHON_EXEC_PREFIX"]="${exec_prefix}"
S["PYTHON_PREFIX"]="${prefix}"
S["PYTHON_VERSION"]="2.7"
S["PYTHON"]="/usr/bin/python"
S["GTK_DOC_USE_LIBTOOL_FALSE"]="#"
S["GTK_DOC_USE_LIBTOOL_TRUE"]=""
S["GTK_DOC_BUILD_PDF_FALSE"]=""
S["GTK_DOC_BUILD_PDF_TRUE"]="#"
S["GTK_DOC_BUILD_HTML_FALSE"]="#"
S["GTK_DOC_BUILD_HTML_TRUE"]=""
S["ENABLE_GTK_DOC_FALSE"]="#"
S["ENABLE_GTK_DOC_TRUE"]=""
S["GTKDOC_DEPS_LIBS"]="-lgobject-2.0 -lglib-2.0"
S["GTKDOC_DEPS_CFLAGS"]="-I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include"
S["HTML_DIR"]="${datadir}/gtk-doc/html"
S["GTKDOC_MKPDF"]="/usr/bin/gtkdoc-mkpdf"
S["GTKDOC_REBASE"]="/usr/bin/gtkdoc-rebase"
S["GTKDOC_CHECK"]="/usr/bin/gtkdoc-check"
S["HAVE_VALGRIND_FALSE"]=""
S["HAVE_VALGRIND_TRUE"]="#"
S["VALGRIND_PATH"]="no"
S["HAVE_CPU_CRISV32_FALSE"]=""
S["HAVE_CPU_CRISV32_TRUE"]="#"
S["HAVE_CPU_CRIS_FALSE"]=""
S["HAVE_CPU_CRIS_TRUE"]="#"
S["HAVE_CPU_X86_64_FALSE"]="#"
S["HAVE_CPU_X86_64_TRUE"]=""
S["HAVE_CPU_M68K_FALSE"]=""
S["HAVE_CPU_M68K_TRUE"]="#"
S["HAVE_CPU_IA64_FALSE"]=""
S["HAVE_CPU_IA64_TRUE"]="#"
S["HAVE_CPU_S390_FALSE"]=""
S["HAVE_CPU_S390_TRUE"]="#"
S["HAVE_CPU_MIPS_FALSE"]=""
S["HAVE_CPU_MIPS_TRUE"]="#"
S["HAVE_CPU_HPPA_FALSE"]=""
S["HAVE_CPU_HPPA_TRUE"]="#"
S["HAVE_CPU_SPARC_FALSE"]=""
S["HAVE_CPU_SPARC_TRUE"]="#"
S["HAVE_CPU_ARM_FALSE"]=""
S["HAVE_CPU_ARM_TRUE"]="#"
S["HAVE_CPU_ARC_FALSE"]=""
S["HAVE_CPU_ARC_TRUE"]="#"
S["HAVE_CPU_ALPHA_FALSE"]=""
S["HAVE_CPU_ALPHA_TRUE"]="#"
S["HAVE_CPU_PPC64_FALSE"]=""
S["HAVE_CPU_PPC64_TRUE"]="#"
S["HAVE_CPU_PPC_FALSE"]=""
S["HAVE_CPU_PPC_TRUE"]="#"
S["HAVE_CPU_I386_FALSE"]=""
S["HAVE_CPU_I386_TRUE"]="#"
S["GST_GCOV_ENABLED_FALSE"]=""
S["GST_GCOV_ENABLED_TRUE"]="#"
S["CCASFLAGS"]=""
S["FFLAGS"]=""
S["CXXFLAGS"]=""
S["GCOV"]=""
S["GCOV_LIBS"]=""
S["GCOV_CFLAGS"]=""
S["VALGRIND_LIBS"]=""
S["VALGRIND_CFLAGS"]=""
S["GST_PACKAGE_ORIGIN"]="Unknown package origin"
S["GST_PACKAGE_NAME"]="GStreamer libav source release"
S["ACLOCAL_AMFLAGS"]="-I m4 -I common/m4"
S["HAVE_ORCC_FALSE"]=""
S["HAVE_ORCC_TRUE"]="#"
S["HAVE_ORC_FALSE"]=""
S["HAVE_ORC_TRUE"]="#"
S["ORCC_FLAGS"]=""
S["ORCC"]=""
S["ORC_LIBS"]=""
S["ORC_CFLAGS"]=""
S["PKG_CONFIG"]="/usr/bin/pkg-config"
S["CPP"]="gcc -E"
S["LT_SYS_LIBRARY_PATH"]=""
S["OTOOL64"]=""
S["OTOOL"]=""
S["LIPO"]=""
S["NMEDIT"]=""
S["DSYMUTIL"]=""
S["MANIFEST_TOOL"]=":"
S["RANLIB"]="ranlib"
S["ac_ct_AR"]="ar"
S["AR"]="ar"
S["LN_S"]="ln -s"
S["NM"]="/usr/bin/nm -B"
S["ac_ct_DUMPBIN"]=""
S["DUMPBIN"]=""
S["LD"]="/usr/bin/ld -m elf_x86_64"
S["FGREP"]="/bin/grep -F"
S["EGREP"]="/bin/grep -E"
S["GREP"]="/bin/grep"
S["SED"]="/bin/sed"
S["am__fastdepCC_FALSE"]="#"
S["am__fastdepCC_TRUE"]=""
S["CCDEPMODE"]="depmode=gcc3"
S["am__nodep"]="_no"
S["AMDEPBACKSLASH"]="\\"
S["AMDEP_FALSE"]="#"
S["AMDEP_TRUE"]=""
S["am__quote"]=""
S["am__include"]="include"
S["DEPDIR"]=".deps"
S["OBJEXT"]="o"
S["EXEEXT"]=""
S["ac_ct_CC"]="gcc"
S["CPPFLAGS"]=""
S["LDFLAGS"]=""
S["CFLAGS"]="-g -O2"
S["CC"]="gcc"
S["LIBTOOL"]="$(SHELL) $(top_builddir)/libtool"
S["OBJDUMP"]="objdump"
S["DLLTOOL"]="false"
S["AS"]="as"
S["GST_LT_LDFLAGS"]=" -version-info 1202:0:1202"
S["GST_LIBVERSION"]="1202:0:1202"
S["GST_AGE"]="1202"
S["GST_REVISION"]="0"
S["GST_CURRENT"]="1202"
S["GST_API_VERSION"]="1.0"
S["MAINT"]=""
S["MAINTAINER_MODE_FALSE"]="#"
S["MAINTAINER_MODE_TRUE"]=""
S["PACKAGE_VERSION_RELEASE"]="1"
S["PACKAGE_VERSION_NANO"]="0"
S["PACKAGE_VERSION_MICRO"]="2"
S["PACKAGE_VERSION_MINOR"]="12"
S["PACKAGE_VERSION_MAJOR"]="1"
S["AM_BACKSLASH"]="\\"
S["AM_DEFAULT_VERBOSITY"]="0"
S["AM_DEFAULT_V"]="$(AM_DEFAULT_VERBOSITY)"
S["AM_V"]="$(V)"
S["am__untar"]="tar -xf -"
S["am__tar"]="tar --format=ustar -chf - \"$$tardir\""
S["AMTAR"]="$${TAR-tar}"
S["am__leading_dot"]="."
S["SET_MAKE"]=""
S["AWK"]="gawk"
S["mkdir_p"]="$(MKDIR_P)"
S["MKDIR_P"]="/bin/mkdir -p"
S["INSTALL_STRIP_PROGRAM"]="$(install_sh) -c -s"
S["STRIP"]="strip"
S["install_sh"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/install-sh"
S["MAKEINFO"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/missing makeinfo"
S["AUTOHEADER"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/missing autoheader"
S["AUTOMAKE"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/missing automake-1.15"
S["AUTOCONF"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/missing autoconf"
S["ACLOCAL"]="${SHELL} /home/rk3188/gst/GStreamer_code/gst-libav-1.12.2/missing aclocal-1.15"
S["VERSION"]="1.12.2"
S["PACKAGE"]="gst-libav"
S["CYGPATH_W"]="echo"
S["am__isrc"]=""
S["INSTALL_DATA"]="${INSTALL} -m 644"
S["INSTALL_SCRIPT"]="${INSTALL}"
S["INSTALL_PROGRAM"]="${INSTALL}"
S["target_os"]="linux"
S["target_vendor"]="pc"
S["target_cpu"]="x86_64"
S["target"]="x86_64-pc-linux-gnu"
S["host_os"]="linux-gnu"
S["host_vendor"]="pc"
S["host_cpu"]="x86_64"
S["host"]="x86_64-pc-linux-gnu"
S["build_os"]="linux-gnu"
S["build_vendor"]="pc"
S["build_cpu"]="x86_64"
S["build"]="x86_64-pc-linux-gnu"
S["target_alias"]=""
S["host_alias"]=""
S["build_alias"]=""
S["LIBS"]=""
S["ECHO_T"]=""
S["ECHO_N"]="-n"
S["ECHO_C"]=""
S["DEFS"]="-DHAVE_CONFIG_H"
S["mandir"]="${datarootdir}/man"
S["localedir"]="${datarootdir}/locale"
S["libdir"]="${exec_prefix}/lib"
S["psdir"]="${docdir}"
S["pdfdir"]="${docdir}"
S["dvidir"]="${docdir}"
S["htmldir"]="${docdir}"
S["infodir"]="${datarootdir}/info"
S["docdir"]="${datarootdir}/doc/${PACKAGE_TARNAME}"
S["oldincludedir"]="/usr/include"
S["includedir"]="${prefix}/include"
S["runstatedir"]="${localstatedir}/run"
S["localstatedir"]="${prefix}/var"
S["sharedstatedir"]="${prefix}/com"
S["sysconfdir"]="${prefix}/etc"
S["datadir"]="${datarootdir}"
S["datarootdir"]="${prefix}/share"
S["libexecdir"]="${exec_prefix}/libexec"
S["sbindir"]="${exec_prefix}/sbin"
S["bindir"]="${exec_prefix}/bin"
S["program_transform_name"]="s,x,x,"
S["prefix"]="/home/installed"
S["exec_prefix"]="${prefix}"
S["PACKAGE_URL"]=""
S["PACKAGE_BUGREPORT"]="http://bugzilla.gnome.org/enter_bug.cgi?product=GStreamer"
S["PACKAGE_STRING"]="GStreamer libav 1.12.2"
S["PACKAGE_VERSION"]="1.12.2"
S["PACKAGE_TARNAME"]="gst-libav"
S["PACKAGE_NAME"]="GStreamer libav"
S["PATH_SEPARATOR"]=":"
S["SHELL"]="/bin/bash"
  for (key in S) S_is_set[key] = 1
  FS = ""

}
{
  line = $ 0
  nfields = split(line, field, "@")
  substed = 0
  len = length(field[1])
  for (i = 2; i < nfields; i++) {
    key = field[i]
    keylen = length(key)
    if (S_is_set[key]) {
      value = S[key]
      line = substr(line, 1, len) "" value "" substr(line, len + keylen + 3)
      len += length(value) + length(field[++i])
      substed = 1
    } else
      len += 1 + keylen
  }

  print line
}
