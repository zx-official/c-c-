/*
    #include <signal.h>
    int sigprocmask(int   how,   const  sigset_t  *set,sigset_t *oldset);
        - 功能：将自定义信号集中的数据设置到内核中(设置阻塞，接触阻塞，替换)
        - 参数：
            - how：如何对内核阻塞信号进行处理
                SIG_BLOCK：将用户设置的阻塞信号集添加到内核中，内核中未被修改的的数据不变
                    假设内核中默认的阻塞信号集是mask， mask | set
                SIG_UNBLOCK:根据用户设置的数据面对内核中的数据进行接触阻塞
                    mask &= ~set
                SIG_SETMASK:覆盖内核中原来的值

            - set：已经初始化好的用户自定义的信号集
            - oldset ：保存设置之前的内核中阻塞信号集的状态，可以值NULL
        - 返回值：
            成功：返回0
            失败：返回-1并设置错误号EFAULT、EINVAL
    
    int sigpending(sigset_t *set);
        -作用：获取内核中的未决信号集
        -参数：set，传出参数，保存的是内核中未决信号集的信息
        - 返回值：0成功-1失败

*/

// 编写一个程序，把所有的常规信号(1-31)的未决状态打印到屏幕
// 设置某些信号是阻塞的，通过键盘产生这些信号

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    //设置二号信号和三号信号阻塞
    sigset_t set;
    sigemptyset(&set);
    //将二号和三号信号集添加
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);

    //修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK,&set,NULL);
    int i;
    int num = 0;
    while (1)
    {
        num++;
        // 获取当前的未决信号集的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);

        //遍历前32位
        for ( i = 1; i <= 31; i++)
        {
            if((sigismember(&pendingset,i)) == 1)
            {
                printf("1");
            }else if(sigismember(&pendingset,i) == 0)
            {
                printf("0");
            }else
            {
                perror("sigismember");
                exit(0);
            }
        }
        printf("\n");
        sleep(1);
        if(num == 10)
        {
            //接触阻塞
            sigprocmask(SIG_UNBLOCK,&set,NULL);
        }
    }
    
    return 0;
}
