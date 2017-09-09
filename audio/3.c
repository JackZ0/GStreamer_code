#include <sys/soundcard.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<pthread.h>
#include<termios.h>     // to realize the immediately key input without pressing enter
#include <stdbool.h>//define true or false - -!

#define SIZE 16//sample size (bit),8bit unsigned
#define CHANNELS 2//audio channels : mono 0 , stereo 1
#define RATE 8000 // sample rate
#define BUFSIZE 320

bool b_flag_start_rec;//the start flag of record
bool b_flag_finish_rec;


pthread_t getchar_id;
static struct termios stored_setting;
void set_immediate_input()
{
    struct termios new_setting;
    tcgetattr(0,&stored_setting);
    new_setting = stored_setting;
    //disable canonical mode,set buffer size to 1
    new_setting.c_lflag &= (~ICANON);
    new_setting.c_cc[VTIME] = 0;
    new_setting.c_cc[VMIN] = 1;
    //set the new attr
    tcsetattr(0,TCSANOW,&new_setting);
}
//----------------default setting------
void default_setting()
{
    tcsetattr(0,TCSANOW,&stored_setting);
}
void *getchar_thread(void *arg)
{
    int vol;//sound volume value
    int fd_mixer;
    //open mixer
    if((fd_mixer = open("/dev/mixer",O_RDWR)) < 0)
    {
        printf("Can not open sound device /dev/mixer\n");
        exit(-1);
    }
    printf("getchar_thread running...\n,thread id:%u\n",pthread_self());
    set_immediate_input();

    if(-1 == ioctl(fd_mixer,MIXER_READ(SOUND_MIXER_VOLUME),&vol))
    {
        perror("ioctl mixer vol failed\n");
    }
    printf("mixer volume : %d %%\n",vol);

    while(1)
    {
        if('q' == getchar())
        {
            printf("\nget key q pressed\n");
            break;
        }
        else if('g' == getchar())
        {
            printf("start record:\n");
            b_flag_start_rec = true;// set the start flag

        }
        else if('s' == getchar())
        {
            printf("stop record:\n");
            b_flag_start_rec = false;// set the start flag
            b_flag_finish_rec = true;

        }
        else if('u' == getchar())
        {
            vol++;
            if(vol>100)
                vol = 100;
            if(vol < 0)
                vol = 0;
            if(-1 == ioctl(fd_mixer,MIXER_WRITE(SOUND_MIXER_VOLUME),&vol))
            {
                perror("ioctl mixer vol failed\n");
            }
            printf("mixer volume : %d %%\n",vol);
        }
        else if('d' == getchar())
        {
            vol--;
            if(vol>100)
                vol = 100;
            if(vol < 0)
                vol = 0;
            if(-1 == ioctl(fd_mixer,MIXER_WRITE(SOUND_MIXER_VOLUME),&vol))
            {
                perror("ioctl mixer vol failed\n");
            }
            printf("mixer volume : %d %%\n",vol);
        }
    }
    default_setting();
    printf("thread quit\n");
    exit(0);
}
main(int argc, char** argv)
{
    printf("#####################################################\n");
    printf("test audio play program 'record'            2010.03.18\n");
    printf("for 16bit,8kHz,stereo wav file only!!!!!!!!\n");
    printf("#####################################################\n");
    int device_id;//the audio fd
    int wav_fd;//write file fd
    int i,j;//temp var
    int arg;//the var to set the parameter of audio device
    int ioctl_status;//the result of ioctl operation
    char audio_buf[BUFSIZE];//the audio buffer, keep audio data

    //open the audio device
    if((device_id = open("/dev/audio",O_RDWR)) < 0)
    {
        printf("Can not open sound device /dev/audio\n");
        exit(-1);
    }
    //open the wav file
    if((wav_fd = open(argv[1],O_RDWR)) < 0)
    {
        printf("can not open %s\n",argv[1]);
        exit(-1);
    }
    //create thread
    int ret;
    ret = pthread_create(&getchar_id,NULL,getchar_thread,NULL);
    if(ret)
        printf("error in create getchar_thread.%derror\n",ret);


    arg = SIZE;
    printf("set sample size:SNDCTL_DSP_SETFMT(%d)",arg);
    ioctl_status = ioctl(device_id,SNDCTL_DSP_SETFMT,&arg);
    if(-1 == ioctl_status)
    {
        perror("ioctl sample size failed");
    }
     //set channels
    arg = CHANNELS;
    printf("set sample size:SNDCTL_DSP_CHANNELS(%d)",arg);
    ioctl_status = ioctl(device_id,SNDCTL_DSP_CHANNELS,&arg);
    if(-1 == ioctl_status)
    {
        perror("ioctl channels failed");
    }
    //set sample rate
    arg = RATE;
    ioctl_status = ioctl(device_id,SNDCTL_DSP_SPEED,&arg);
    if(-1 == ioctl_status)
    {
        perror("ioctl rate failed");
    }
    //read some audio data, and write them to the device
    printf("read %s and write it to audio device \n",argv[1]);

    b_flag_start_rec = false;
    b_flag_finish_rec = false;
    printf("please push key s to start record...\n");
    while(1)
    {
        while(b_flag_start_rec)
        {
            i = read(device_id,audio_buf,BUFSIZE);
            write(wav_fd,audio_buf,i);
            printf("r");

        }
        if(b_flag_finish_rec)
        {
            if(wav_fd>0)
                close(wav_fd);//close the file for reopen
            printf("== rec done ==\n");
        }

        if(b_flag_finish_rec)// play the rec file
        {
              //reopen the wav file so it back to the begin of the record file
            if((wav_fd = open(argv[1],O_RDWR)) < 0)
            {
                printf("can not open %s\n",argv[1]);
                exit(-1);
            }
            while(1)
            {
                i = read(wav_fd,audio_buf,BUFSIZE);
            //  printf("i:%d ",i);
                if(i > 0)
                {
            //          printf("read %d bytes from %s\n",i,argv[1]);
                    printf(".");
                    int size_w;
                    size_w = write(device_id,audio_buf,i);
                //      printf("j:%d . write -->%dbytes to dsp",j,size_w);
                    j++;
                }
                else
                {
                    printf("break\n");
                    close(wav_fd);
                    break;
                }
            }
            printf("end of read file");
        }//if(b_flag_finish_rec)        
    }


    //close fds
    //  close(wav_fd);
    close(device_id);
}

