/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t wait(int *wstatus);
        功能：等待任意一个子进程结束，如果任意一个子进程结束了，此函数会回收他的资源
        参数: int *wstatus
            进程退出时的状态信息，传入的是一个int类型的地址，传出参数
        返回值：
            - 成功：返回被回收的子进程的id
            - 失败： 返回-1 (所有的子进程都结束，调用函数失败)
    调用wait函数的进程会被挂起（阻塞），知道他的一个子进程退出或收到一个不能被忽略的信号
    如果没有子进程了，会立刻返回-1，如果子进程都结束了 ，也会立即返回-1
       pid_t waitpid(pid_t pid, int *wstatus, int options);

*/
#include <sys/types.h>
#include <sys/wait.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc, char const *argv[])
{
    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid; 

    //创建5个子进程
    for (int i = 0; i < 5; i++)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }
    
    if(pid >0)
    {
        //父
        while ((1))
        {
          printf("parent,pid = %d\n",getpid());
          wait(NULL);
          sleep(1);
        }
        
        
    }else if(pid == 0)
    {
        printf("child, pid :%d\n",getpid());
    }
    return 0;
}
