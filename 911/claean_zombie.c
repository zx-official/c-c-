#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    
    pid_t pid = fork();
    if (pid == 0)
    {
        //child process
        printf("i am child process pid is %d , parent is %d \n",getpid(),getppid());
    }else if(pid > 0)
    {
        //parent peocess
        signal(SIGCHLD,SIG_IGN);
        printf("i am parent process pid = %d , parent is %d \n",getpid(),getppid());
        while (1)
        {
            /* code */
        }
           
    }

    
    return 0;
}
