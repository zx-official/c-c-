/*
    #include<stdio.h>
    void exit(int status);
    调用退出处理函数
    刷新i/o缓存，关闭文件描述符
    调用_exit()系统调用
    进程终止运行

    #include<unistd.h>
    void _exit(int ststus);
    
status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以接收到改信息
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    printf("hello\n");
    // \n printf内部能自动作刷新io缓冲区功能
    printf("world");

    _exit(0);
    return 0;
}
