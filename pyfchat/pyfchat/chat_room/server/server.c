/* 文件名：server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "wrap.h"
#include "user_linkedlist.h"
#include "message_processing.h"
#include "administrator.h"

#define SERV_PORT 8000       //端口号

int main(int argc, char **argv)
{
	int i, maxi, maxfd, listenfd, connfd, sockfd;        //socket描述符
	int nready, client[FD_SETSIZE];      //client存储客服端描述符的数组 
	ssize_t n; 
	fd_set temp_set, allset;      //定义集合  fd_set定义储存文件描述符的
	char str[INET_ADDRSTRLEN];   //ipv4地址字符串的长度   
	socklen_t cliaddr_len;       //客服端ip长度
	struct sockaddr_in	cliaddr, servaddr;  //存放IP的结构体

	//link_user p;
    link_msg from_client_message;         //定义来自客户端的消息结构体
    from_client_message = (link_msg)malloc(sizeof(*from_client_message));
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	Listen(listenfd, 20);

    /* 服务器显示所有注册用户帐号密码信息,并将其链入用户链表 */
    display_user_list();     //显示所有注册用户信息(ID与密码)
	
    /*打开所有消息记录文件*/
    int fd = open("./all_chat_record.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open ./all_chat_record.txt");
        return -1;
    }
    
    maxfd = listenfd;		/* initialize */
	maxi = -1;			/* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
		client[i] = -1;	/* -1 indicates available entry */
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);       //将listenfd放入allset集合中

	for ( ; ; ) 
	{
		temp_set = allset;	/* structure assignment 结构分配*/
        /*temp_set哪几个变化，temp_set为输入输出参数。nread变化的数量*/
		nready = select(maxfd+1, &temp_set, NULL, NULL, NULL);  //select阻塞中，time置NULL
		if (nready < 0)
			perr_exit("select error");
        //printf("nready : %d\n",nready);

		if (FD_ISSET(listenfd, &temp_set)) 
		{ /* new client connection */
			cliaddr_len = sizeof(cliaddr);
			connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);

			if (MONITORING_CLIENT_OPEN)
                printf("IP为 %s 端口号为 %d 的客户端已开启\n",
			       inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
			       ntohs(cliaddr.sin_port));
            from_client_message->feedback = MONITORING_CLIENT_HEALTH_TIPS;
            Write(connfd, from_client_message, sizeof(*from_client_message));
            memset(from_client_message, 0, sizeof(*from_client_message));

			for (i = 0; i < FD_SETSIZE; i++)
				if (client[i] < 0) 
                {
					client[i] = connfd; /* save descriptor */
					break;
				}
            //printf("client number : %d\n",i);
			if (i == FD_SETSIZE) {
				fputs("too many clients\n", stderr);
				exit(1);
			}

			FD_SET(connfd, &allset);	/* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd; /* for select */
			if (i > maxi)
				maxi = i;	/* max index in client[] array */
            
			if (--nready == 0)
				continue;	/* no more readable descriptors */
		}

		for (i = 0; i <= maxi; i++) 
        {	/* check all clients for data */
            if ( (sockfd = client[i]) < 0)
				continue;
			//printf("maxi : %d\n",maxi);
			if (FD_ISSET(sockfd, &temp_set)) 
            {
				if ( (n = Read(sockfd,from_client_message, sizeof(*from_client_message))) == 0) 
                {
			        if (MONITORING_CLIENT_CLOSE)
			            printf("ID地址为 %s 端口号为 %d 的客户端已关闭\n",
			                inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
			                ntohs(cliaddr.sin_port));
					/* connection closed by client */
					FD_CLR(sockfd, &allset);
					client[i] = -1;
                    link_user p = search_connfd(sockfd);
                    if (p != NULL)
                    {
                        p->user_status = DOWNLINE;     //将下限用户状态置DOWNLINE，下线
                        p->connfd = -1;
                    }
					Close(sockfd);
				} else 
                {
                    message_processing(sockfd, from_client_message, fd);
				}

				if (--nready == 0)
					break;	/* no more readable descriptors */
			} //end if
		}  //end for
	} //end for(;;)
} //end main

