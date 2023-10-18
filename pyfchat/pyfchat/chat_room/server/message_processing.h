/* 文件名：message_processing.h */

#ifndef _MESSAGE_PROCESSING_H_
#define _MESSAGE_PROCESSING_H_
#include "administrator.h"

//#define MSG_LEN 200                 //消息的长度
#define USER_DATA_LEN 40            //帐号 密码 的最大总长度

/*     用户登录状态 在user_linkedlist.h中定义        */
/*     用户登录状态 下线     上线    隐身    离开    */
//enum user_status{ DOWNLINE,ON_LINE,STEALTH,LEAVE};

/*   用户注册登录        注册ID检验    注册 登录ID检验      登录密码检验          登录 */
enum user_register_login{REG_ID_JUDGE, REG, LOGIN_ID_JUDGE, LOGIN_PASSWORD_JUDGE, LOG};
/*   查询信息类型     查询在线ID        帮助  用户下限并返回主页面  用户改变登录状态 */
enum inquire_msg_type{VIEW_ON_LINE = 5, HELP, HOME,                 RELOGIN};
/*   聊天类型  私聊检验           私聊     退出私聊      群聊   聊天前禁言检验*/
enum chat_type{WHISPER_JUDGE = 9, WHISPER, EXIT_WHISPER, GROUP, SILENCE_JUDGE};
/*   管理员特殊权限           将用户踢出聊天室 禁言     关闭服务器以及所有客户端 增加管理员*/
enum adminastrator_privileges{KICKED_OUT = 14, SILENCE, CLOSE,                   ADDING_ADMIN};
/*   非作者的管理员            管理员判断       管理员申请*/
enum not_author_adminastrator{ADMIN_JUDGE = 18, ADMIN_APPLY};

typedef struct user_msg* link_msg;     //储存消息结构体
struct user_msg
{
    char src_ID[17];                //发消息人ID
    char dest_ID[17];               //收消息人ID
    char whisper_receiver_ID[17];   //私聊接收方ID
    char msg[MSG_LEN];              //消息内容
    int  msg_type;                  //消息类型
    int  feedback;                  //命令反馈类型
};

/* 将user_linkedlist.c文件中的head设为全局变量，以便在本函数中使用方便 */
extern link_user head;              

/*声明*/
int current_minute(void);
void display_user_list(void);
int open_user_data_file(void);
char register_ID_judgment(char *msg);
char login_ID_judgment(int sockfd, link_msg p_client);
char login_password_judgment(char *msg);
void login(int sockfd,link_msg p_client);
void view_online_ID(int sockfd,link_msg p_client);
void user_downline(int sockfd,link_msg p_client);
void change_login_status(int sockfd,link_msg p_client);
int whisper_judgment(link_msg p_client);
void whisper_message(int sockfd,link_msg p_client,int fd);
void search_receive_ID(link_msg p_client);
void group_chat(int sockfd,link_msg p_client,int fd);
void kicked_out_user(int sockfd,link_msg p_client);
void silence_user(int sockfd,link_msg p_client);
void silence_judgment(int sockfd,link_msg p_client);
void close_server_client(int sockfd,link_msg p_client);
void administrator_judgment(int sockfd,link_msg p_client);
void administrator_application(int sockfd,link_msg p_client);
void author_adding_administrator(int sockfd,link_msg p_client);
void message_processing(int sockfd,link_msg p_client, int fd);

#endif
