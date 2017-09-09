#include <sys/soundcard.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
    /* id：读取音频文件描述符；fd：写入的文件描述符。i，j为临时变量*/
    int id,fd,i,j;
    /* 存储音频数据的缓冲区，可以调整*/
    char testbuf[4096];
    /* 打开声卡设备，失败则退出*/
    if ( ( id = open ( "/dev/audio", O_RDWR ) ) < 0 )
    {
         fprintf (stderr, " Can't open sound device!\n");
         exit ( -1 ) ;
    }
    /* 打开输出文件，失败则退出*/
    if ( ( fd = open ("./test.wav",O_RDWR))<0)
    {
         fprintf ( stderr, " Can't open output file!\n");
         exit (-1 );
    }
    /* 设置适当的参数，使得声音设备工作正常*/
    /* 详细情况请参考linux关于声卡编程的文档*/
    i=0;
    ioctl (id,SNDCTL_DSP_RESET,(char *)&i) ;
    ioctl (id,SNDCTL_DSP_SYNC,(char *)&i);
    i=1;
    ioctl (id,SNDCTL_DSP_NONBLOCK,(char *)&i);
    i=8000;
    ioctl (id,SNDCTL_DSP_SPEED,(char *)&i);
    i=1;
    ioctl (id,SNDCTL_DSP_CHANNELS,(char *)&i);
    i=8;
    ioctl (id,SNDCTL_DSP_SETFMT,(char *)&i);
    i=3;
    ioctl (id,SNDCTL_DSP_SETFRAGMENT,(char *)&i);
    i=1;
    ioctl (id,SNDCTL_DSP_PROFILE,(char *)&i);
    /* 读取一定数量的音频数据，并将之写到输出文件中去*/
    for ( j=0; j<100;)
    {
        i=read(id,testbuf,4096);
        if(i>0)
        {
             write(fd,testbuf,i);
             j++;
        }
    }
    /* 关闭输入、输出文件*/
    close(fd);
    close(id);
    exit(0);
}
