#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <sys/errno.h>
int main(int argc, char const *argv[])
{
    int msid;
    char msgbuf[100];
    if((msid = msgget(0x1234, 0666|IPC_CREAT)) == -1) 
    {
        fprintf(stderr,"open %d queue failed \n",0x1234);
        return ;
    }
    while (strncmp(msgbuf,"quit",4) != 0)
    {
        memset(msgbuf,0,sizeof(msgbuf));
        fgets(msgbuf,sizeof(msgbuf),stdin);
        while (msgsnd(msid,msgbuf,strlen(msgbuf),0) < 0)
        {
            if (errno == EINTR)
            continue;

            return;
        }
        

    }
    
    return 0;
}
