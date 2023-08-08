/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    //打开一个已经存在的文件
    int open(const char *pathname, int flags);
    参数：
        pathname：要打开的文件绝对路径
        flag:文件的操作权限
             是一个宏表示对文件的操作类型，把他放在<sys/types.h>和<fcntl.h>中以便于其他函数也调用
    文档中这么写：
    The  argument  flags  must  include  one of the following access modes:
    O_RDONLY, O_WRONLY, or O_RDWR
    分别代表只读，只写，可读可写 这三个参数是互斥的

    返回一个文件描述符   调用失败 值为-1

    errno:属于linux系统函数，是库里的全局变量，记录的是最近错误号

    #include <stdio.h>
    void perror(const char *s);
    作用：答应errno对应的错误描述
    *s：用户描述
    例如 perrpr("open")
    输出： open: No such file or directory  open是用户描述的open


    int open(const char *pathname, int flags, mode_t mode);
    在c++中才有函数的重载，这里第二个open是可变参数



*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
    int fd = open("a.txt",O_RDONLY);
    //fd: files descriptor 文件描述符
    if (fd == -1)
    {
        perror("open");
    }
    //关闭
    close(fd);
    return 0;
}
