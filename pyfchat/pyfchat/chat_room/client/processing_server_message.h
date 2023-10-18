/*文件名：processing_server_message.h */

#ifndef _PROCESSING_SERVER_MESSAGE_H_
#define _PROCESSING_SERVER_MESSAGE_H_

void print_login_staus(link_msg p_server);
void current_time(void);
void return_current_time(char *buf);
int open_client_chat_logs_file(char *buf);
int processing_server_message(int sockfd,link_msg p_server,int fd);

#endif
