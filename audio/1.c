#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/soundcard.h>
/* 下面的三个参数是跟具体文件相关的，文件什么样，就要设置成什么样 */
#define RATE 44100 
#define SIZE 16     
#define CHANNELS 2  // 1表示单声道，2为立体声
/* ................ */
unsigned char buf[RATE*SIZE/8]; //buf里面正好放一秒钟的音频，下面的计时还要用
int main()
{
    int fd;
    int wavfd; //wav文件的描述符
    int arg;        /* ..ioctl..... */
    int status;   /* ........ */
                /* ...... */
    fd = open("/dev/dsp", O_RDWR);
    if (fd < 0) {
        printf("open of /dev/dsp failed");
        exit(1);
}
    wavfd = open("./10.wav",O_RDONLY);
    if (wavfd < 0) {
        printf("open of wav failed");
        exit(1);
  }

/* .......... */
    arg = SIZE;
    status = ioctl(fd, SOUND_PCM_WRITE_BITS, &arg);
    if (status == -1)
         perror("SOUND_PCM_WRITE_BITS ioctl failed");
    if (arg != SIZE)
         perror("unable to set sample size");

/* .......... */
    arg = CHANNELS;
    status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &arg);
    if (status == -1)
        perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
    if (arg != CHANNELS)
        perror("unable to set number of channels");

/* .......... */
     arg = RATE;
         status = ioctl(fd, SOUND_PCM_WRITE_RATE, &arg);
     if (status == -1)
         perror("SOUND_PCM_WRITE_WRITE ioctl failed");
    /* 从wav文件中读buf大小的内容，然后写入/etc/dsp中，直到文件结束 */
     int time = 0; //动态显示播放时间用

     while (status = read(wavfd, buf, sizeof(buf)) > 0) {
         write(fd, buf, sizeof(buf));
         printf("%ds, enjoy .../n",time++);

          /* 以下三句，用于在更改播放文件的参数时，播放掉缓冲区内的内容，可以用，更保险*/
//         status = ioctl(fd, SOUND_PCM_SYNC, 0);
  //         if (status == -1)
    //           perror("SOUND_PCM_SYNC ioctl failed");

        }
}

