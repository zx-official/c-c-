/*
    #include <signal.h>
    int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
        
        - 作用：检查或改变信号的出了，信号捕捉
        - 参数：
            - signum：需要捕捉的信号的变化或者宏值（信号的名称）
            - act： 捕捉到信号之后的处理动作
            - oldact：唱一次对信号捕捉相关的设置，一般不使用传递NULL
        - 返回值：
            成功返回0，失败返回-1

    struct sigaction 
    {
        //函数指针，指向的函数就是信号捕捉哦到之后的处理函数
        void     (*sa_handler)(int);
        //不常用
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        //临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号
        sigset_t   sa_mask;
        //使用哪一个信号处理对捕捉到信号进行一个处理
        int        sa_flags;
        常用的有：
            0：表示使用handler
            SA_SIGINFO：表示使用sa_sigaction
        
        //被废弃，指定NULL
        void     (*sa_restorer)(void);
    };

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

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = &myalarm;

    //清空临时阻塞信号集
    sigemptyset(&act.sa_mask);

    //注册信号捕捉
    sigaction(SIGALRM,&act,NULL);


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
    while (1)
    {
    
    }
    
    return 0;
}