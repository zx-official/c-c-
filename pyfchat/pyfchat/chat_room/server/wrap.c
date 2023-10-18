/*************************************************************
  文件名：wrap.c
  功能：提供各种服务器端操作函数
*************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/******************************************************
 函数名：Read
 函数功能：从文件描述符fd所对应的文件或套接字中读取数据
 输入参数：fd,要读取数据的文件所对应的描述符
           ptr,存放读取数据的缓冲区首地址
		   nbytes, 想要读取到的字节数
 返回值：实际最终读取到的字节数            
******************************************************/
ssize_t Read(int fd, void *ptr, size_t nbytes)
{
	ssize_t n;

again:
	if ((n = read(fd, ptr, nbytes)) == -1)
	{
		if (errno == EINTR)
		{
			goto again;
		}
		else
		{
		    printf("Read failed.\n");
			return -1;
		}
	}
	return n;
}

/******************************************************
 函数名：Write
 函数功能：将数据写入文件描述符fd所对应的文件或套接字中
 输入参数：fd,要写入数据的文件所对应的描述符
           ptr,存放待写数据的首地址
           nbytes, 想要写入的字节数
 返回值：实际最终写入的字节数          
******************************************************/
ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
	ssize_t n;

again:
	if ((n = write(fd, ptr, nbytes)) == -1)
	{
		if (errno == EINTR)
		{
			goto again;
		}
		else
		{
			printf("Write failed.\n");
			return -1;
		}
	}
	return n;
}

/******************************************************
 函数名：perr_exit
 函数功能：从终端打印出错信息并强制退出进程
 输入参数：s，为传递的要打印信息字符串的首地址
 返回值：空            
******************************************************/
void perr_exit(const char *s)
{
	perror(s);
	exit(1);
}

/******************************************************
  函数名：Socket
  函数功能：创建一个用于网络通信的套接字
  输入参数：family, 为通信协议簇
            type,为套接字类型
			protocol,为sockt所使用的协议编号，在一般情况下设为0即可
  返回值：函数执行成功返回非负的sockt套接字描述符           
******************************************************/
int Socket(int family, int type, int protocol)
{
	int n;
	if ((n = socket(family, type, protocol)) < 0)
	{
		perr_exit("Socket error");
	}
	return n;
}

/******************************************************
  函数名：Bind
  函数功能：将套接字描述符fd和网络通用的结构体指针sa绑定在一起
  输入参数：fd,为sockt套接字描述符
            sa,为网络通用的结构体指针
            salen,为结构体sa的长度
  返回值：空        
******************************************************/
void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
    perr_exit("Bind error");
}

/******************************************************
  函数名：Listen
  函数功能：创建一个等待队列，在其中存放未处理的客户端连接请求，
            声明套接字描述符fd处于监听状态，将该套接字描述符用于
			监听客户端的连接请求
  输入参数：fd,为sockt套接字描述符
            backlog, 为请求队列中允许的最大连接请求数
  返回值：空        
******************************************************/
void Listen(int fd, int backlog)
{
	if (listen(fd, backlog) < 0)
   	perr_exit("Listen error");
}

/******************************************************
  函数名：Connect
  函数功能：客户端建立sockt套接字后，向服务器发出连接请求
  输入参数：fd,为sockt套接字描述符
            sa,为网络通用的结构体指针
			salen,为结构体sa的长度
  返回值：空        
******************************************************/
void Connect(int fd, const struct sockaddr *sa, int salen)
{
	if ((connect(fd, sa, salen)) < 0)
	{
		perr_exit("Connect error");
	}
}

/******************************************************
  函数名：Accept
  函数功能：服务器等待并接收客户端的连接请求
  输入参数：fd,为sockt套接字描述符
  输出参数：accept函数执行成功返回时，sa可传出已经成功连接后
            客户端的地址和端口号
			salenptr, 传出客户端地址结构体的实际长度
  返回值：与客户端进行通信的描述符      
******************************************************/
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int n;
    
again:
	if ( (n = accept(fd, sa, salenptr)) < 0) 
	{
		if ((errno == ECONNABORTED) || (errno == EINTR))
		{
	    	goto again;
		}	
		else
		{
			perr_exit("Accept error");
		}	
	}
	return n;
}

/******************************************************
  函数名：Close
  函数功能：关闭fd所对应的文件或套接字
  输入参数：fd,为sockt套接字描述符或文件描述符
  返回值：空        
******************************************************/
void Close(int fd)
{
	if (close(fd) == -1)
	{
		perr_exit("Close error");
	}
}


