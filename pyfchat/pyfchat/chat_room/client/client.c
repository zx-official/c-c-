/****************************************************
  函数名：client.c
  函数功能：与服务器进行通信
  返回值：检测主函数是否执行完毕
****************************************************/
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "wrap.h"
#include "home_page.h"
#include "processing_terminal_message.h"
#include "processing_server_message.h"

#define SERV_PORT 8000
int main(int argc,char *argv[] )                   
{
	struct sockaddr_in servaddr;
	int sockfd;
	int fd;          //本ID聊天记录文件的描述符
	int nready;
    char ip[20];
	int n;                                       /* 从终端键盘或服务器的连接中读取到数据字节数 */  
    
	fd_set inset;
	fd_set tmp_inset;
	link_msg from_terminal; 
    link_msg from_server;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    if (argc == 1)
    {
        strcpy(ip,"127.0.0.1");
    }else
    {
        strcpy(ip,argv[1]);
    }

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(SERV_PORT);
    
	Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	from_terminal = (link_msg)malloc(sizeof(*from_terminal));
	if (from_terminal == NULL)
	{
		perror("out of memory.\n");
	}
	from_server = (link_msg)malloc(sizeof(*from_server));
	if (from_server == NULL)
	{
		perror("out of memory.\n");
	}

    /* 显示温馨小贴士 */
    Read(sockfd, from_terminal, sizeof(*from_terminal));
    if (from_terminal->feedback)
    {
        health_tips();          //健康小贴士
        sleep(from_terminal->feedback);
    }

home_page: 
    /*处理注册，登录，退出*/
    login_processing(sockfd,from_terminal);      
    
    /*打开一个属于用户自己的聊天记录文件*/
    fd = open_client_chat_logs_file(from_terminal->src_ID);
server_page: 
    printf("您已进入聊天室服务界面\n");
    printf("您本次登录的ID为 ： %s\n",from_terminal->src_ID);
    if (strncmp(from_terminal->src_ID, "pyfadmin", 8) == 0)
    {
        printf("***************************************************\n");
        printf("尊贵的聊天室作者 潘熠飞 您好,欢迎您对本聊天室的管理\n");
        printf("              您的管理员特权已全面开通             \n");
        printf("***************************************************\n");
    }
    printf("输入 help/ 可以查询使用方法\n      祝您聊天愉快\n");
	
	FD_ZERO(&inset);
	FD_SET(sockfd, &inset);            /* 将与服务器进行通信的描述符添加到集合inset中 */
	FD_SET(0, &inset);                 /* 将标准输入描述符添加到集合inset中 */   
	while (1)
	{
		tmp_inset = inset;   

		/* 监视所有添加到集合tmp_inset中的描述符，如果该描述符所对应的连接或终端文件有数据
		   写入的时候就读取数据，如果都没有数据就将添加到集合tmp_inset中的所有描述符堵塞直到有数据到来 */
		nready = select(sockfd + 1, &tmp_inset, NULL, NULL, NULL);
		if (nready < 0)
		{
			perror("select failed.\n");
		}
		if (FD_ISSET(sockfd, &tmp_inset) > 0) /* 检测sockfd所对应的与服务器建立的连接中是否有数据到达 */            
		{
		   
		    int flag;
            /* 如果有数据，就读取该数据 */
			n = Read(sockfd, from_server, sizeof(*from_server));  
			if (n == 0)
			{
				printf("服务器已关闭.\n");           /* 服务器已关闭 */
                if(atexit(close_prompt)!=0)
                    printf("can't register myexit2\n");
	   			exit(0);                             /* 检测到服务器关闭则客户端也关闭 */ 
			}
            //printf("from_server : %s\n",from_server->msg);
            
			/* 解析从服务器端发来的信息 */
			flag = processing_server_message(sockfd, from_server, fd);
			if(flag == HOME)
			{
				Close(fd);              //用户下线后关闭聊天记录文件
                goto home_page;
			}
		}

    	if (FD_ISSET(0, &tmp_inset) > 0)             // 检测标准输入所对应的终端键盘是否有数据到达 
		{
	        memset(from_terminal->msg, 0 , sizeof(from_terminal->msg));	    //接收数据前清空

			/* 如果有数据，从终端键盘读取数据 */
			n = Read(0, from_terminal->msg, sizeof(from_terminal->msg));  
            cancel_spaces(from_terminal->msg);         //将从终端输入的信息删除空格
            //printf("检测键盘输入位数 %d\n",strlen(from_terminal->msg));
            
            /* 处理来自终端键盘的数据 */
            if((processing_terminal_message(sockfd,from_terminal,fd)) != -2)
                //Write(sockfd, from_terminal, sizeof(*from_terminal));
                ;
            else
                printf("您的输入格式不对，请重新输入\n");
        }

		if (--nready == 0)                 //只有一个描述符(0或sockfd)所对应的终端文件或套接字有数据到达
		{
			continue;                      //处理完该数据后，重新再返回到select在继续检测是否有数到达
		}
	}
	Close(sockfd);
	return 0;
}
