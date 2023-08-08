/*
    SIGCHLD信号产生的3个条件
        1.子进程结束
        2.子进程暂停了
        3.子进程继续运行
        都会给父进程发送该信号，父进程默认忽略该信号

    使用SIGCHILD信号解决僵尸进程问题
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
void myFun (int num)
{
    printf("捕捉到的信号： %d\n",num);
    //回收子进pcb的资源
    while (1)
    {
        int ret = waitpid(-1,NULL,WNOHANG);
        if (ret > 0)
        {
            printf("child die pid = %d\n",ret);
        }else if(ret == 0)
        {
            //说明还有孩子活着
            break;
        }else if (ret == -1)
        {
            break;
        }
    }
    
}
int main(int argc, char const *argv[])
{
    //提前设置好阻塞信号集
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGCHLD);
    //sigprocmask(SIG_BLOCK,&set,NULL);  一种阻塞方式
    pid_t pid ;
    int i;
    for ( i = 0; i < 10; i++)
    {
        pid = fork();
        if(pid == 0)
        {
            break;
        }
    }
    if(pid >0)
    {
        //父进程收到SIGCHLD回收进程
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigemptyset(&act.sa_mask);
        
        act.sa_mask =set;   //另一种阻塞方式

        sigaction(SIGCHLD,&act,NULL);
        //父进程
        while (1)
        {
            
            printf("parent process pid : %d\n",getpid());
            sleep(2);
        }
        
    }else if (pid == 0)
    {
        printf("child process pid : %d\n",getpid());
    }
    return 0;
}
