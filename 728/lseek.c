/*
    #include <sys/types.h>
    #include <unistd.h>
    off_t lseek(int fd, off_t offset, int whence);
        参数：
            -fd：文件描述符，通过open得到的,通过fd操作问价
            -offset: 偏移量
            -whence:
                seek_set:
                    设置文件指针的偏移量
                seek_cur：
                    设置偏移量：当前位置 + 第二个参数offset的值
                seek_end；
                    设置偏移量：文件大小 + 第二个参数offset的值
        作用：
        1.移动文件指针到文件头
        lseek(fd, 0, SEEK_SET);

        2.获取当前文件指针的位置
        lseek(fd, 0, SEEK_CUR);

        3.获取长度
        lseek(fd, 0, SEEK_END);

        4拓展文件的长度,当前文件10b,110b,增加100个字节
        leek( fd, 100, SEEK_END)
        汉族一：需要写一次和数据

*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char const *argv[])
{
    int fd = open("hello.txt",O_RDWR);
    if(fd == -1)
    {
        perror("open");
        return -1;
    }

    //扩展文件的长度
    int ret = lseek(fd,100,SEEK_END);
    if (ret == -1)
    {
        perror("lseek");
        return -1;
    }
    //写入空数据
    write(fd," ",1);

    close(fd);
    return 0;
}
