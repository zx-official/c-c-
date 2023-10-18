/*****************************************************************
  文件名：wrap.h
  功能：提供服务器端各种操作函数的声明
*****************************************************************/
#ifndef _WRAP_H_
#define _WRAP_H_

void perr_exit(const char *s);

ssize_t Read(int fd, void *ptr, size_t nbytes);

ssize_t Write(int fd, void *ptr, size_t nbytes);

int Socket(int family, int type, int protocol);

void Bind(int fd, const struct sockaddr *sa, socklen_t salen);

void Listen(int fd, int backlog);

void Connect(int fd, const struct sockaddr *sa, int salen);

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);

void Close(int fd);


#endif 
