/*
    #include <signal.h>
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
        - 功能：设置某个信号的捕捉行为
        - 参数：
            - signum：要捕捉的信号
            - handler：捕捉到信号要如何处理
                 - SIG_IGN ：忽略信号
                 - SIG_DFT： 使用信号默认的行为
                 - 回调函数：这个函数是内核调用，程序员只负责写，捕捉到信号后如何去处理信号
                        - 需要程序员实现，提前准备好的，函数的类型根据实际的需求，看函数指针的定义
                        - 不是程序员调用，而是当信号产生，由内核调用
                        - 函数指针是实现回调函数的手段，而函数实现后，将函数名放到函数值指针的位置即可
        
        - 返回值：
                成功，返回上一次注册的信号处理函数的地址，第一次调用返回NULL
                失败，返回SIG_ERR，设置错误号

    SIGKILL SIGSTOP不能被捕捉，不能被忽略
*/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>

void myalarm(int num) 
{
    printf("捕捉到的信号的编号是 ：%d\n",num);
    printf("xxxxxxx\n");
}
// 过三秒后，每隔两秒钟定时一次
int main(int argc, char const *argv[])
{
    //注册信号
   // signal(SIGALRM,SIG_IGN);
   // signal(SIGALRM,SIG_DFL);
   // void (*sighandler_t)(int); 函数指针 int类型的参数表示捕捉到信号的值
    __sighandler_t val = signal(SIGALRM,&myalarm);
    if(val == SIG_ERR)
    {
        perror("signal");
        exit(0);
    }
    struct itimerval new_value;

    // 初始化
    // 间隔的时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;

    // 延迟的时间
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    int ret = setitimer(ITIMER_REAL, &new_value, NULL); // 非阻塞的
    printf("begin...\n");
    if (ret == -1)
    {
        perror("setitimer");
        exit(0);
    }
    getchar();
    return 0;
}