/***********************************************************************
文件名：message_processing.c  
文件功能：处理来自各个客户端的各种信息 
          将聊天消息保存至聊天记录文件 all_chat_record.txt 中
核心函数：message_processing
***********************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "wrap.h"
#include <time.h>
#include "user_linkedlist.h"
#include "message_processing.h"
#include "administrator.h"

/***********************************************************************
文件名：current_time
文件功能：输出当前时间
调用关系：被processing_server_message调用
参数：存放当前时间的字符串
返回值：无
***********************************************************************/
void current_time(char *buf)
{
    struct tm *ptr; 
    time_t localTime; 
    //char str[80]; 
    localTime=time(NULL); 
    ptr=localtime(&localTime); 
    //strftime(str,100," %F %X",ptr); 
    strftime(buf,100," %X",ptr);       //将当前时间保存至字符数组str中
    //printf("%s\n",str);                //打印当前时间
}

/************************************************************
函数名：current_minute
功能介绍:将当前的分钟数返回(小时*60+分钟)
调用关系：被kicked_out_user调用
参数：无
返回值：当前的分钟数
************************************************************/
int current_minute(void)
{
    struct tm *ptr; 
    time_t localTime; 
    char str[80]; 
    localTime=time(NULL); 
    ptr=localtime(&localTime); 
    strftime(str,100,"%H%M",ptr);       //将当前时间保存至字符数组str中
    //printf("%s\n",str);                //打印当前时间
    //printf("len:%d\n",strlen(str));
    int temp = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        temp = temp * 10 + (*(str + i) - '0');
    }
    int hour = temp / 100;         
    int minute = temp % 100;
    return hour * 60 + minute;             //返回总分钟数
}

/************************************************************
函数名：display_user_list
功能介绍：在开启服务器之后,
          将所有注册用户的ID 密码 登录状态 禁言标志
          链入用户链表
调用关系：被server.c文件中的int main()调用
参数：无
返回值：无
************************************************************/
void display_user_list(void)
{
    char buf[USER_DATA_LEN];                   //创建一个保存用户ID密码信息的缓冲字符串
    link_user p;
    FILE *fp = fopen("./user_data.txt", "a+");               /* 打开存储用户ID和密码的文件 */     
    if (fp == NULL)
    {
        perror("error open ./user_data.txt");
    } 

    /*将所有已注册用户的ID,密码,登录状态等信息链入用户链表*/
    while (fgets(buf, sizeof(buf), fp) != NULL)    
    {
        p = make_node(buf, DOWNLINE);           //初始化所有用户都下线
        insert(p);
    }

    fclose(fp);                            //关闭文件
    
    if (MONITORING_DISPLAY_USER_LIST)
    {
        printf("\n所有注册用户ID与密码信息如下：\n");
        traverse();                            //遍历所有用户并显示ID 密码
    }
}

/************************************************************
函数名：open_user_data_file
功能介绍：打开储存用户用户 ID 与 密码 信息的文件
调用关系：被message_processing调用
参数：无
返回值：返回打开的文件描述符
************************************************************/
int open_user_data_file(void)
{
    int fd;
    fd = open("./user_data.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open ./all_chat_record.txt");
        return -1;
    }
    return fd;
}

/************************************************************
函数名：register_ID_judgment
功能介绍：判断申请注册的ID是否已被注册
调用关系：被message_processing调用
参数：传入需要判断的ID号
返回值：已注册返回1   未注册返回0
************************************************************/
char register_ID_judgment(char *msg)
{
    /* 服务器显示客户端注册ID请求 */
    if (MONITORING_USER_REGISTER_REQUEST)
        printf("对客服端注册ID %s 检验\n",msg);
    
    link_user p = search_ID(msg);   //p为查找指定ID的数据结构体
    if (p == NULL)
        return '0';
    else
        return '1';
}

/************************************************************
函数名：login_ID_judgment
功能介绍：判断登录ID是否成功
调用关系：被message_processing调用
          调用current_minute
参数：传入需要登录的ID号
返回值：未注册返回0   已登录返回1  可以登录返回2
************************************************************/
char login_ID_judgment(int sockfd, link_msg p_client)
{
    /* 服务器显示客户端登录ID请求 */
    if (MONITORING_USER_LOGIN_REQUEST)
        printf("对客户端登录ID %s 检验\n",p_client->msg);

    link_user p = search_ID(p_client->msg);   //p为查找指定ID的数据结构体

    if (p == NULL)
        p_client->feedback = 0;        //该用户未注册     
    else if (p->user_status != DOWNLINE)
        p_client->feedback = 1;    //该用户已登录 
    else
    {
        if (p->kicked_out != 0)            //被踢出
        {
            /* 此处有BUG啊，时间过一天会有问题的,未做修复 */
            int minute = current_minute();
            if ((minute - (p->kicked_out) >= LOGIN_WAIT_TIME)
                    || ((minute < p->kicked_out)
                    && (1440 - p->kicked_out + minute > 5))) 
            {
                p_client->feedback = 3;             //可以登录
            }
            else
            {
                p_client->feedback = 2;             //还需等待几分钟
                memset(p_client->msg, 0, sizeof(p_client->msg));
                *(p_client->msg) = LOGIN_WAIT_TIME + '0';
            }
        }
        if (p->kicked_out == 0)             //未被踢出
        {
            p_client->feedback = 3;             //可以登录
        }
    }
    Write(sockfd, p_client, sizeof(*p_client));
}

/************************************************************
函数名：login_password_judgment
功能介绍：判断登录ID的密码是否匹配
调用关系：被message_processing调用
参数：传入需要登录ID的密码
返回值：密码错误返回0   密码正确返回1  
************************************************************/
char login_password_judgment(char *msg)
{
    
    link_user p = search_ID(msg);   //p为查找指定ID的数据结构体
    int len_password, len_ID, len_password_client;
    char buf_password[17];
    len_ID = mystrlen(msg);                          
    len_password_client = mystrlen(msg + len_ID + 1);
    
    /* 将客户端发来的密码赋给 buf_password */
    strncpy(buf_password, msg + len_ID + 1, len_password_client);
    *(buf_password + len_password_client) = '\0';
    len_password = strlen(p->user_password);
    
    /* 服务器显示客户端登录密码请求 */
    if (MONITORING_USER_LOGIN_REQUEST)
        printf("对客户端登录密码 %s 检验\n", buf_password);
    
    if ((strncmp(p->user_password,msg + len_ID + 1,len_password_client) == 0)
            && (len_password == len_password_client))
    {
        return '1';             //密码正确返回'1'
    }
    else
        return '0';          //密码不正确返回'0'

}

/************************************************************
函数名：login
功能介绍：判断登录ID的密码是否匹配
调用关系：被message_processing调用
参数：传入需要登录用户的ID，密码，登录状态
返回值：无
************************************************************/
void login(int sockfd,link_msg p_client)
{
    int len_ID = mystrlen(p_client->msg);       //登录帐号长度
    strncpy(p_client->src_ID, p_client->msg, len_ID + 1);
    int len_password = mystrlen(p_client->msg + len_ID + 1);      //登录密码长度
    int login_status = *(p_client->msg + len_ID + len_password + 2) - '0';  //登录状态
    link_user p_login = search_ID(p_client->src_ID);   //查找登录ID 
    p_login->connfd = sockfd;             //将与该客户端的套接字赋给connfd
    p_login->user_status = login_status;  //user_status记录登录状态 下线0 上线1 隐身2 离开3
    p_login->kicked_out = 0;              //去除登录等待时间
    
    /* 显示用户登录状态 */
    if (MONITORING_USER_LOGIN_STATUS)
    {
        switch (login_status)
        {
            case ON_LINE:
            {
                printf("用户 %s 已登录 状态为 ： 在线\n",p_client->src_ID);
                break;
            }
            case STEALTH:
            {
                printf("用户 %s 已登录 状态为 ： 隐身\n",p_client->src_ID);
                break;
            }
            case LEAVE:
            {
                printf("用户 %s 已登录 状态为 ： 离开\n",p_client->src_ID);
                break;
            }
            case NO_DISTURB:
            {
                printf("用户 %s 已登录 状态为 ： 免扰\n",p_client->src_ID);
                break;
            }
        }
    }

    /* 向其他在线用户发出指定用户重新登录通知 */
    memset(p_client->msg, 0, sizeof(p_client->msg));
    *p_client->msg = login_status + '0';
    p_client->msg_type = RELOGIN;
    if (login_status != STEALTH)
    {   
        p_client->feedback = 1;                               //反馈标志置为1表示向其他登录用户通报
        link_user p;
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->connfd != p_login->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd, p_client, sizeof(*p_client));     
            }
        }
    }
}

/************************************************************
函数名：view_online_ID
功能介绍：查询在线ID
调用关系：被message_processing调用
          调用view_online_ID
参数：传入记录在线ID的字符串
返回值：无
************************************************************/
void view_online_ID(int sockfd,link_msg p_client)
{
    /* 调用查找在线ID函数 位于user_linkedlist.c中 */
    link_user p_src = search_ID(p_client->src_ID);
    memset(p_client->msg, 0, sizeof(p_client->msg));
    if (MONITORING_USER_ONLINE_ID_QUERY)
        printf("用户 %s 查询了在线ID \n",p_client->src_ID);
    link_user p ;
    int len_ID,len = 0;
    /* 普通用户查询在线ID时 不包括隐身ID  */
    if (p_src->administrator == -1)
    {
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->user_status != STEALTH))
            {
                len_ID = strlen(p->user_ID);
                strncpy(p_client->msg + len,p->user_ID,len_ID);
                *(p_client->msg + len_ID + len) = '\n';
                len += len_ID + 1;
            }
        }
        *(p_client->msg + len) = '\0';
    }

    /* 管理员查询在线ID时 包括隐身ID  */
    if (p_src->administrator == 1)
    {
        for (p = head; p; p = p->next)
        {
            if (p->user_status != DOWNLINE)
            {
                len_ID = strlen(p->user_ID);
                strncpy(p_client->msg + len,p->user_ID,len_ID);
                *(p_client->msg + len_ID + len) = '\n';
                len += len_ID + 1;
            }
        }
        *(p_client->msg + len) = '\0';
    }
    Write(sockfd,p_client,sizeof(*p_client));
}

/************************************************************
函数名：user_downline
功能介绍：将指定ID下线,向申请下线用户通报已经下线
          并向其他所有已登录用户通报该用户已经下线
调用关系：被message_processing调用
参数：sickfd,申请下线用户与服务器的套接字,
      p_client,从服务器发来的消息结构体
返回值：无
************************************************************/
void user_downline(int sockfd,link_msg p_client)
{
    link_user p;
    p = search_ID(p_client->src_ID);          //找到申请者
    
    if (p == NULL)
    {
        if (MONITORING_USER_DOWNLINE)
            printf("此ID没有注册\n");
        return;
    }
    else if (p->user_status != DOWNLINE)      //向申请下线用户通报
    {
        /* 服务器显示用户下线 */
        if (MONITORING_USER_DOWNLINE)
            printf("用户 %s 已下线\n",p_client->src_ID);

        p->user_status = DOWNLINE;
        p_client->feedback = 0;
        Write(sockfd,p_client,sizeof(*p_client));
    }

    /* 向所有在线用户通报该ID已近下线 */
    for (p = head; p; p = p->next)      
    {
        if (p->user_status != DOWNLINE)
        {
            sockfd = p->connfd;
            p_client->feedback = 1;
            Write(sockfd,p_client,sizeof(*p_client));
        }
    }
}

/************************************************************
函数名：change_login_status
功能介绍：将申请用户状态改变,向其通报已改变的登录状态
          并向其他所有已登录用户通报该用户已改变的登录状态
调用关系：被message_processing调用
参数：sickfd,申请改变登录状态用户与服务器的套接字,
      p_client,从服务器发来的消息结构体
返回值：无
************************************************************/
void change_login_status(int sockfd,link_msg p_client)
{
    int login_status = *(p_client->msg) - '0';         //记录改变的状态
    link_user p = search_ID(p_client->src_ID);         //找到申请改变用户
    p->user_status = login_status;                     //修改该用户的状态
    p_client->feedback = 0;                            //反馈标志置为0表示向申请用户通报
    
    /* 服务器显示申请改变登录状态用户新的登录状态  */
    if (MONITORING_USER_LOGIN_STATUS)
    {
        if (login_status == ON_LINE)
            printf("%s 已上线\n",p->user_ID);
        if (login_status == STEALTH)
            printf("%s 已隐身\n",p->user_ID);
        if (login_status == LEAVE)
            printf("%s 已离开\n",p->user_ID);
        if (login_status == NO_DISTURB)
            printf("%s 已免扰\n",p->user_ID);
    }

    /* 向申请者通报已经改变的登录状态 */
    Write(sockfd,p_client,sizeof(*p_client));
    
    /* 如果改变的登录状态不为隐身，则向其他登录用户通报该用户已改变的登录状态 */
    if (login_status != STEALTH)
    {   
        p_client->feedback = 1;                        //反馈标志置为1表示向其他登录用户通报
        link_user p_relogin = search_ID(p_client->src_ID);  //找到申请人
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->connfd != p_relogin->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd,p_client,sizeof(*p_client));     //向其他在线用户发出指定用户重新登录通知
            }
        }
    }
}

/************************************************************
函数名：whisper_judgment
功能介绍：判断私聊接收者是否可以接收私聊消息
调用关系：被message_processing调用
参数：p_client,从服务器发来的消息结构体
      包括私聊发起者ID 与 私聊接收者ID
返回值：
        返回0：接收方ID未注册 
        返回1：接收方未上线 
        返回2：接收方为自己 
        返回3：接收方状态为离开 
        返回4：接收方状态为免扰 
        返回5：接收方可以接收私聊消息 
************************************************************/
int whisper_judgment(link_msg p_client)
{
    /* 服务器显示用户私聊申请 */
    if (MONITORING_USER_WHISPER_REQUEST)
        printf("用户 %s 申请私聊\n",p_client->src_ID);

    link_user p = search_ID(p_client->whisper_receiver_ID);  //找到接收方
    if (p == NULL)
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("此ID没有注册\n");
        p_client->feedback = 0;
        return 0;
    }
    else if (p->user_status == 0)
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("该用户没有上线\n");
        p_client->feedback = 1;
        return DOWNLINE;
    }
    else if (strcmp(p_client->src_ID,p_client->whisper_receiver_ID) == 0)
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("该ID为自己,不能发送聊天信息\n");
        p_client->feedback = 2;
        return 2;
    }
    else if (p->user_status == LEAVE)
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("该用户已离开，可能无法及时回复\n");
        p_client->feedback = 3;
        return LEAVE;
    }
    else if (p->user_status == NO_DISTURB)
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("该用户状态为请勿打扰，无法回复您的信息\n");
        p_client->feedback = 4;
        return NO_DISTURB;
    }
    else 
    {
        if (MONITORING_USER_WHISPER_REQUEST)
            printf("该用户可以接收数据\n");
        p_client->feedback = 5;
        return 5;
    }
}

/************************************************************
函数名：whisper_message
功能介绍：判断接收方是否可以接收私聊消息 
          如果可以接收：
          向私聊发送方发出成功发送私聊消息提示
          向私聊接收方发出私聊消息
          将私聊消息保存到聊天记录文件中
调用关系：被message_processing调用
          调用whisper_judgment
参数：sockfd 私聊发起者与服务器间的套接字
      p_client,从服务器发来的消息结构体
      包括私聊发起者ID 与 私聊接收者ID 私聊消息
      fd 为聊天记录文件的描述符
返回值：空
************************************************************/
void whisper_message(int sockfd,link_msg p_client,int fd)
{
    int len_msg = strlen(p_client->msg);                        //计算消息长度
    link_user p = search_ID(p_client->whisper_receiver_ID);     //找到私聊接收方
    link_user p_src = search_ID(p_client->src_ID);              //找到私聊发送方
    int flag = whisper_judgment(p_client);                      //判断私聊接收方是否可以接收私聊消息 
    
    /* 接收方状态为离开 */
    if(flag == 3)
    {
        p_client->feedback = 3;
        Write(sockfd,p_client,sizeof(*p_client));
    }
    /* 接收方已下线 */
    else if(flag == DOWNLINE)
    {
        p_client->feedback = DOWNLINE;
        Write(sockfd,p_client,sizeof(*p_client));
    }
    /* 接收方状态为免扰 */
    else if(flag == 4)
    {
        p_client->feedback = NO_DISTURB;
        Write(sockfd,p_client,sizeof(*p_client));
    }
    /* 接收方可以接收私聊消息 */
    if (flag == 5 || flag == 3)
    {
        /* 服务器显示发送:1成功的私聊消息 */
        if (MONITORING_USER_WHISPER_CONTENTS)
        {
            printf("用户 %s 向 用户 %s 发送私聊消息:\n",
                    p_client->src_ID, p_client->whisper_receiver_ID);
            printf("%s\n",p_client->msg);
        }

        /* 向私聊接收方发送聊天消息 */
        p_client->feedback = 1;
        sockfd = p->connfd;                          //将接收方的套接字赋给sockfd
        if ((len_msg) != 0 && (p->user_status != NO_DISTURB))
            Write(sockfd,p_client,sizeof(*p_client));    

        /*向私聊发出方发出成功发送消息提示*/
        p_client->feedback = 2;
        sockfd = p_src->connfd;                      //将发送方的套接字赋给sockfd
        Write(sockfd,p_client,sizeof(*p_client));    //向私聊发起方发送聊天消息

        /* 将私聊信息写入聊天记录文件 */
        char buf[10];
        current_time(buf);
        Write(fd, "\n", 1);                        
        Write(fd, p_client->src_ID, strlen(p_client->src_ID));
        Write(fd, " (whisper)", 10);
        Write(fd, buf, 9);
        Write(fd, "\n", 1);
        Write(fd, "\t", 1);
        Write(fd, "send to ", 8);
        Write(fd, p_client->whisper_receiver_ID, strlen(p_client->whisper_receiver_ID));
        Write(fd, " / ", 3);
        Write(fd, p_client->msg, strlen(p_client->msg));
        Write(fd, "\n", 1);
    }
}

/************************************************************
函数名：search_recerve_ID
功能介绍：为group_chat函数服务
          查找所有可以接收群聊消息的用户ID
          (为保护用户，不包括登录状态为隐身的用户，)
调用关系：被group_chat调用
参数：p_client,从服务器发来的消息结构体
      包括 群聊发起者ID 与 群聊消息
返回值：空
************************************************************/
void search_receive_ID(link_msg p_client)
{
    link_user p;
    link_user p_src = search_ID(p_client->src_ID);  //找到群聊发起者
    int len_ID,len = 0;

    memset(p_client->msg, 0, sizeof(p_client->msg));
    /* 将除群聊发起者 与 登录状态为隐身的用户以外的已登录用户ID赋给消息结构体中的msg 
       每个ID间以'\n'隔开，结尾以'\0'结束 */
    for (p = head; p; p = p->next)
    {
        if ((p->user_status != DOWNLINE) 
                && (p->user_status != STEALTH)
                && (p->connfd != p_src->connfd)
                && (p->user_status != NO_DISTURB))
        {
            len_ID = strlen(p->user_ID);
            strncpy(p_client->msg + len, p->user_ID, len_ID);
            *(p_client->msg + len_ID + len) = '\n';
            len += len_ID + 1;
        }
    }
    *(p_client->msg + len) = '\0';         //结尾处+'\0'
}

/************************************************************
函数名：group_chat
功能介绍：处理群聊消息
          如果聊天室内没有其他用户登录 将告知群聊发起者发送失败
          如果群聊消息发送成功：
              向所有可以接收群聊消息的用户发送群聊消息
              向群聊发起者发送成功接收群聊消息的用户ID列表
              将群聊消息保存至聊天记录文件中
调用关系：被message_processing调用
参数：sockfd,群聊发起者与客户端的套接字
      p_client,从服务器发来的消息结构体
      包括 群聊发起者ID 与 群聊消息
      fd,聊天记录文件的描述符
返回值：空
************************************************************/
void group_chat(int sockfd,link_msg p_client,int fd)
{
    link_user p;
    link_user p_src = search_ID(p_client->src_ID);     //找到群聊发起者

    /* 反馈标志为0表示向群聊接收方发出群聊信息 */
    p_client->feedback = 0;                            
    int num = 0;              //记录成功接收群聊消息用户的数量
    char buf[10];
    current_time(buf);

    for (p = head; p; p = p->next)
    {
        if ((p->user_status != DOWNLINE) 
                && (p->connfd != p_src->connfd)
                && (p->user_status != NO_DISTURB))
        {
            strncpy(p_client->dest_ID, p->user_ID, strlen(p->user_ID) + 1);
            sockfd = p->connfd;
            Write(sockfd,p_client,sizeof(*p_client));
            num++;

            /* 将群聊消息写入文件 */
            if (num == 1)
            {
                Write(fd, "\n", 1);
                Write(fd, p_client->src_ID, strlen(p_client->src_ID));
                Write(fd, " (group)", 8);
                Write(fd, buf, 9);
                Write(fd, "\n", 1);
            }
            Write(fd, "\tsend to ", 9);
            Write(fd, p_client->dest_ID, strlen(p_client->dest_ID));
            Write(fd, " / ", 3);
            Write(fd,  p_client->msg, strlen(p_client->msg));
            Write(fd, "\n", 1);
        }
    }
    
    /* 服务器显示发送成功的群聊消息 */
    if (num > 0)
    {
        if (MONITORING_USER_GROUP_CHAT_CONTENTS)
        {
            printf("用户 %s 发出群聊消息:\n",
                    p_client->src_ID);
            printf("%s\n",p_client->msg);
        }
    }

    /* 向群聊的发起者发送接收成功ID列表 */
    sockfd = p_src->connfd;           
    if (num == 0)                     //如果没有用户在线 将msg清空
        memset(p_client->msg, 0,sizeof(*(p_client->msg)));

    /* 反馈标志为1表示向群聊发起方发出群聊信息 */
    p_client->feedback = 1;

    /* 将msg置为 接收用户ID+群聊消息 */
    char buf_msg[MSG_LEN];            //储存群聊消息的缓冲字符串
    strcpy(buf_msg, p_client->msg);
    search_receive_ID(p_client);
    int len_msg = strlen(p_client->msg);
    *(p_client->msg + len_msg) = '\0';
    strcpy(p_client->msg + len_msg + 1, buf_msg);
    Write(sockfd,p_client,sizeof(*p_client));
}

/************************************************************
函数名：kecked_out_user
功能介绍：处理管理员踢人命令
          如果被踢出用户未注册 或 未登录 向管理员回复踢人失败
          如果成功踢出用户：
              向管理员回复踢人成功
              向被踢出用户提示已被管理员踢出用户
              向其他登录用户发出该用户被踢出聊天室通知
调用关系：被message_processing调用
参数：sockfd,管理员与客户端的套接字
      p_client,从服务器发来的消息结构体
      包括 管理员ID 与 被踢出用户ID
返回值：空
************************************************************/
void kicked_out_user(int sockfd,link_msg p_client)
{
    link_user p_kicked = search_ID(p_client->msg);      //找到要踢出的用户
    link_user p_admin = search_ID(p_client->src_ID);    //找到管理员
    strcpy(p_client->dest_ID, p_client->msg);           //将要踢出的用户赋给p_client->dest_ID
    memset(p_client->msg, 0, sizeof(p_client->msg));    //清空msg
    
    /* 向管理员回复被踢出者没有注册 */
    if (p_kicked == NULL)
    {
        if (MONITORING_ADMINISTRATOR_KICKED_OUT_USER)
            printf("尊敬的管理员,您踢出的用户没有注册\n");
        p_client->feedback = 0;
        Write(sockfd,p_client,sizeof(*p_client));      
        return;
    }
    /* 向管理员回复被踢出者没有登录 */
    else if (p_kicked->user_status == DOWNLINE)
    {
        if (MONITORING_ADMINISTRATOR_KICKED_OUT_USER)
            printf("尊敬的管理员,您踢出的用户不在线\n");
        p_client->feedback = 1;
        Write(sockfd,p_client,sizeof(*p_client));      
        return;
    }
    /* 踢人成功 */
    else if ((p_kicked->administrator == -1) 
            || ((strncmp(p_client->src_ID, "pyfadmin", 8) == 0)
            && (strlen(p_client->src_ID) == 8)))
    {
        /* 服务器显示管理员成功踢出用户 */
        if (MONITORING_ADMINISTRATOR_KICKED_OUT_USER)
            printf("尊敬的管理员,您已成功踢出用户 %s\n",p_client->dest_ID);

        /* 向管理员回复踢人成功信息 */
        p_client->feedback = 2;
        Write(sockfd,p_client,sizeof(*p_client));      
        
        /* 向被踢出用户发出踢人信息 */
        p_client->feedback = 3;
        p_kicked->user_status = DOWNLINE;
        sockfd = p_kicked->connfd;
        p_kicked->kicked_out = current_minute();
        Write(sockfd,p_client,sizeof(*p_client));     
        
        /* 向其他已登录用户发出指定用户被踢出通知 */
        p_client->feedback = 4;
        link_user p;
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->connfd != p_kicked->connfd) 
                    && (p->connfd != p_admin->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd,p_client,sizeof(*p_client));     
            }
        }
    }
    else
    {
        /* 向管理员回复踢出用户为管理员信息，失败 */
        p_client->feedback = 5;
        Write(sockfd,p_client,sizeof(*p_client));      
    }
}

/************************************************************
函数名：silence_user
功能介绍：处理管理员禁言与解除禁言命令
          如果指定用户未注册 或 未登录 向管理员回复命令失败
          如果成功禁言 或 解除禁言指定用户：
              向管理员回复命令成功
              向指定用户提示已被管理员禁言 或 解除禁言
              向其他登录用户发出该用户被禁言 或 解除禁言通知
调用关系：被message_processing调用
参数：sockfd,管理员与客户端的套接字
      p_client,从服务器发来的消息结构体
      包括 管理员ID 与 被禁言用户ID
返回值：空
************************************************************/
void silence_user(int sockfd,link_msg p_client)
{
    link_user p = search_ID(p_client->msg);             //找到指定用户ID
    strcpy(p_client->dest_ID, p_client->msg);           //将指定用户ID赋给dest_ID
    memset(p_client->msg, 0, sizeof(*p_client->msg));   //将msg清空
    
    /* 向管理员回复被禁言用户没有注册 */
    if (p == NULL)
    {
        if (MONITORING_ADMINISTRATOR_SILENCE_USER)
            printf("尊敬的管理员,您禁言的用户未注册\n");
        p_client->feedback = 0;
        Write(sockfd,p_client,sizeof(*p_client));      
        return;
    }
    /* 向管理员回复被禁言用户没有登录 */
    else if (p->user_status == DOWNLINE)
    {
        if (MONITORING_ADMINISTRATOR_SILENCE_USER)
            printf("尊敬的管理员,您禁言的用户未登录\n");
        p_client->feedback = 1;
        Write(sockfd,p_client,sizeof(*p_client));      //向管理员回复禁言信息
        return;
    }
    /* 禁言成功  */
    else if ((p->administrator == -1) 
            || ((strncmp(p_client->src_ID, "pyfadmin", 8) == 0)
            && (strlen(p_client->src_ID) == 8)))
    {
        /* 向管理员回复命令成功 */
        p_client->feedback = 2;
        /* silence记录对指定用户禁言 或解除禁言 */
        p->silence = -(p->silence);                     
        *p_client->msg = p->silence + '0';
        
        /* 服务器显示禁言 或 解除禁言命令 */
        if (MONITORING_ADMINISTRATOR_SILENCE_USER)
        {
            if (p->silence == 1)
                printf("尊敬的管理员 %s,您已成功对用户 %s 禁言\n",
                        p_client->src_ID,p_client->dest_ID);
            else
                printf("尊敬的管理员 %s,您已成功对用户 %s 解除禁言\n",
                        p_client->src_ID,p_client->dest_ID);
        }

        Write(sockfd,p_client,sizeof(*p_client));      
        
        /* 向指定用户发出禁言 或解除禁言命令 */
        p_client->feedback = 3;
        sockfd = p->connfd;
        Write(sockfd,p_client,sizeof(*p_client));     
        
        /* 向其他已登录用户发出指定用户被禁言 或 解除禁言命令 */
        p_client->feedback = 4;
        link_user p_silence = search_ID(p_client->dest_ID);
        link_user p_admin = search_ID(p_client->src_ID);
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->connfd != p_silence->connfd) 
                    && (p->connfd != p_admin->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd,p_client,sizeof(*p_client));     
            }
        }
    }
    else
    {
        /* 向管理员回复踢出用户为管理员信息，失败 */
        p_client->feedback = 5;
        Write(sockfd,p_client,sizeof(*p_client));      
    }
}

/************************************************************
函数名：silence_judgment
功能介绍：判断申请发送聊天消息的用户是否处于被禁言状态
调用关系：被message_processing调用
参数：sockfd,申请方与客户端的套接字
      p_client,从服务器发来的消息结构体
      包括 申请方ID 与 聊天消息
返回值：空
************************************************************/
void silence_judgment(int sockfd,link_msg p_client)
{
    /* 服务器显示用户申请聊天信息 */
    if (MONITORING_USER_CHAT_REQUEST)
        printf("用户 %s 申请聊天\n",p_client->src_ID);
    
    link_user p =search_ID(p_client->src_ID);          //找到申请发送聊天消息的用户
    if (p->silence == 1)
        p_client->feedback = 1;                        //如果该用户被禁言 反馈1
    else
        p_client->feedback = -1;                       //如果该用户未被禁言 反馈-1
    Write(sockfd,p_client,sizeof(*p_client));     
}

/************************************************************
函数名：close_server_client
功能介绍：处理来自管理员的关闭服务器 与 所有客户端命令
调用关系：被message_processing调用
参数：p_client,从服务器发来的消息结构体
      包括 管理员ID
返回值：空
************************************************************/
void close_server_client(int sockfd,link_msg p_client)
{
    /* 服务器显示管理员发布关闭服务器以及所有客户端指令 */
    if (MONITORING_ADMINISTRATOR_CLOSE_SERVER_CLIENT)
        printf("管理员 %s 已发布关闭服务器以及所有客户端指令\n",p_client->src_ID);
    
    link_user p;    
    
    /* 向所有已登录用户发出关闭服务器指令 */
    for (p = head; p; p = p->next)
    {
        if (p->user_status != DOWNLINE)
        {
            p_client->feedback = CLOSE_COUNTDOWN;
            sockfd = p->connfd;
            Write(sockfd,p_client,sizeof(*p_client));     
        }
    }
    
    int second = CLOSE_COUNTDOWN;                           //关闭服务器缓冲秒数
    while (second)
    {
        if (MONITORING_ADMINISTRATOR_CLOSE_SERVER_CLIENT)
            printf("距离服务器和所有客户端关闭还有 %d 秒\n",--second);
        sleep(1);
    }
    if (MONITORING_ADMINISTRATOR_CLOSE_SERVER_CLIENT)
        printf("服务器以及所有客户端已经关闭\n");
}

void administrator_judgment(int sockfd,link_msg p_client)
{
    link_user p = search_ID(p_client->src_ID);              //找到申请人ID
    if (p->administrator == 1)
        p_client->feedback = 1;
    else
        p_client->feedback = 0;
    Write(sockfd,p_client,sizeof(*p_client));
}

void administrator_application(int sockfd,link_msg p_client)
{
    int len_password = strlen(password);        //普通用户申请成为管理员所需要的密码长度
    int len_msg = strlen(p_client->msg);        //普通用户申请成为管理员所需要的密码长度
    link_user p_apply = search_ID(p_client->src_ID);    //找到申请人ID
    
    if (p_apply->silence == 1)
    {
        if (MONITORING_USER_APPLICATION_ADMINISTRATOR)
            printf("用户 %s 已被禁言,无法申请管理员身份\n",p_apply -> user_ID);
        p_client->feedback = 2;
        Write(sockfd, p_client, sizeof(*p_client));
        return ;
    }
    else if ((strncmp(password, p_client->msg, len_password) == 0)
            && (len_msg == len_password))
    {
        /* 向申请者发送申请成功信息 */
        p_client->feedback = 1;
        p_apply->administrator = 1;
        if (MONITORING_USER_APPLICATION_ADMINISTRATOR)
            printf("用户 %s 申请管理员权限成功\n",p_client->src_ID);
        Write(sockfd, p_client, sizeof(*p_client));
        
        /* 向其他已登录用户发出指定用户申请成功管理员 */
        p_client->feedback = 3;
        link_user p;
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) && (p->connfd != p_apply->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd, p_client, sizeof(*p_client));     
            }
        }
        return ;
    }
    else
    {
        p_client->feedback = 0;
        if (MONITORING_USER_APPLICATION_ADMINISTRATOR)
            printf("用户 %s 申请管理员权限失败\n",p_client->src_ID);
        Write(sockfd, p_client, sizeof(*p_client));
    }
}

void author_adding_administrator(int sockfd,link_msg p_client)
{
    link_user p_dest = search_ID(p_client->dest_ID);
    if (p_dest == NULL)
    {
        printf("作者 %s 添加的管理员ID未注册\n",p_client->dest_ID);
        p_client->feedback = 0;
        Write(sockfd,p_client,sizeof(*p_client));   
        return;
    }
    
    /* 向作者反馈设置管理员情况 */
    link_user p_src = search_ID(p_client->src_ID);
    p_client->feedback = 1;
    p_dest->administrator = -(p_dest->administrator);    
    memset(p_client->msg, 0, sizeof(p_client->msg));
    *(p_client->msg) = p_dest->administrator + '0';
    Write(sockfd,p_client,sizeof(*p_client));   

    /* 向目标用户反馈设置管理员情况 */
    if (p_dest->user_status != DOWNLINE)
    {
        p_client->feedback = 2;
        sockfd = p_dest->connfd;
        Write(sockfd,p_client,sizeof(*p_client));  
    }

    /* 如果新添加的管理员状态不为隐身，则向其他已登录用户反馈设置管理员情况 */
    link_user p;
    p_client->feedback = 3;
    if (p_dest->user_status != STEALTH)
    {
        for (p = head; p; p = p->next)
        {
            if ((p->user_status != DOWNLINE) 
                    && (p->connfd != p_src->connfd) 
                    && (p->connfd != p_dest->connfd))
            {
                sockfd = p->connfd;
                Write(sockfd,p_client,sizeof(*p_client));     
            }
        }
    }
}

/************************************************************
函数名：message_processing  (本文件内的核心函数)
功能介绍：处理来自客户端的一切信息
          处理指令如下：
              用户帐号的申请 登录 下线
              用户改变登录状态 私聊 群聊 查询在线用户 
              管理员特殊权限：
                  踢人 禁言 关闭服务器
                   
调用关系：被server.c文件中的 int main() 调用
          调用函数如下：
              int open_user_data_file(void);
              char register_ID_judgment(char *msg);
              char login_ID_judgment(char *msg);
              char login_password_judgment(char *msg);
              void login(char *msg);
              void view_online_ID(link_msg p_client);
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
              
参数：sockfd,为客户端与服务器联系的套接字
      p_client,从服务器发来的消息结构体
      fd 为聊天记录文件的描述符
返回值：空
************************************************************/
void message_processing(int sockfd,link_msg p_client, int fd)
{
    int fd_user = open_user_data_file();              //打开用户帐号 密码信息记录的文件
    char flag;                                        //记录登录注册成功与否的标志
    
    /* 判断消息类型 处理各种消息 */
    switch (p_client->msg_type)
    {
        case REG_ID_JUDGE:        //处理用户注册ID判断信息
        {
            flag = register_ID_judgment(p_client->msg);
            Write(sockfd, &flag, 1);
            break;
        }
        case REG:
        {
            int len_msg = strlen(p_client->msg);
            Write(fd_user,p_client->msg,len_msg);
            Write(fd_user,"\n",1);
            Close(fd_user);
            link_user p = make_node(p_client->msg, DOWNLINE);
            insert(p);
            break;
        }
        case LOGIN_ID_JUDGE:
        {
            flag = login_ID_judgment(sockfd,p_client);
            break;
        }
        case LOGIN_PASSWORD_JUDGE:
        {
            flag = login_password_judgment(p_client->msg);
            Write(sockfd, &flag, 1);
            break;
        }
        case LOG:
        {
            login(sockfd,p_client);
            break;
        }
        case VIEW_ON_LINE:
        {
            view_online_ID(sockfd,p_client);
            break;
        }
        case HELP:
        {
            if (MONITORING_USER_HELP_QUERY)
                printf("ID为 %s 的用户查询了帮助界面\n ",p_client->src_ID);
            break;
        }
        case HOME:
        {
            user_downline(sockfd,p_client);
            break;
        }
        case RELOGIN:
        {
            change_login_status(sockfd,p_client);
            break;
        }
        case WHISPER_JUDGE:
        {
            whisper_judgment(p_client);
            Write(sockfd,p_client,sizeof(*p_client));
            break;
        }
        case WHISPER:
        {
            //printf("接收到 %s 发来的聊天内容 : %s\n",p_client->src_ID,p_client->msg);
            whisper_message(sockfd, p_client, fd);
            break;
        }
        case EXIT_WHISPER:
        {
            if (MINOTORING_USER_DISCONNET_WHISPER)
                printf("%s 与 %s 的私聊关系已断开\n",p_client->src_ID,p_client->msg);
            break;
        }
        case GROUP:
        {
            group_chat(sockfd, p_client, fd);
            break;
        }
        case KICKED_OUT:
        {
            kicked_out_user(sockfd,p_client);
            break;
        }
        case CLOSE:
        {
            close_server_client(sockfd,p_client);
            exit(0);
        }
        case SILENCE:
        {
            silence_user(sockfd,p_client);
            break;
        }
        case SILENCE_JUDGE:
        {
            silence_judgment(sockfd,p_client);
            break;
        }
        case ADMIN_JUDGE:
        {
            administrator_judgment(sockfd,p_client);
            break;
        }
        case ADMIN_APPLY:
        {
            administrator_application(sockfd,p_client);
            break;
        }
        case ADDING_ADMIN:
        {
            author_adding_administrator(sockfd,p_client);
            break;
        }
    }
}
