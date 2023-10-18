/*****************************************************
文件名：user_linkedlist.h
*****************************************************/

#ifndef _USER_LINKEDLIST_H_
#define _USER_LINKEDLIST_H_

typedef struct user_data *link_user;     //储存所有用户的 帐号 密码
struct user_data
{
    char user_ID[17];              //用户帐号
    char user_password[17];        //用户密码
    int user_status;               //一个ID的状态
    int connfd;                    //服务器与一个进程间的套接字
    int silence;                   //记录用户禁言状态 1表示禁言 0表示正常
    int administrator;             //置1为管理员 置0为普通用户
    int kicked_out;                //退出状态判断，被踢出置当前分钟数，正常退出为0
    link_user next;
};

/*用户的状态     下线      上线     隐身     离开   请勿打扰     */
enum user_status{DOWNLINE, ON_LINE, STEALTH, LEAVE, NO_DISTURB};

int mystrlen(const char *src);
link_user make_node(char *buf, int user_status);
void free_node(link_user p);
void insert(link_user p);
void traverse(void);
void turn_node(void);
int search_status(link_user p);
link_user search_ID(char *msg);
link_user search_connfd(int sockfd);

#endif
