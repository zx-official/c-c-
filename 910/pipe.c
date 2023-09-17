#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    int pipe1[2];
    int ret1 = pipe(pipe1);
    if (ret1 != 0)
    {
        perror("pipe1");
        exit(1);
    }

    int pipe2[2];
    int ret2 = pipe(pipe2);
    if (ret2 != 0)
    {
        perror("pipe2");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        /* child process */
        close(pipe1[0]);
        close(pipe2[1]);
        char buf[1024] = {0};
        char *little = "hello, world";
        write(pipe1[1],little,strlen(little));
        read(pipe2[0],buf,sizeof(buf));
        printf("child recv:\n");
        write(STDOUT_FILENO,buf,sizeof(buf));


    }
    if (pid > 0)
    {
        // parent process
        char buf[1024] = {0};
        close(pipe1[1]);
        close(pipe2[0]);
        char *big = "HELLO,WORLD";
        write(pipe2[1],big,strlen(big));
        read(pipe1[0],buf,sizeof(buf));
        printf("parent recv\n");
        write(STDOUT_FILENO,buf,sizeof(buf));

    }
    
    
    
    return 0;
}
