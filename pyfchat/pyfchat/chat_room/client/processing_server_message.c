/***********************************************************************
文件名：processing_server_message.c
文件功能：处理来自服务器的各种信息
主干函数：processing_server_message
调用关系：被server.c文件中的main函数调用
***********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include "home_page.h"
#include "processing_server_message.h"
#include "processing_terminal_message.h"

/***********************************************************************
文件名：open_client_chat_logs_file
文件功能：当登录成功后，打开该用户聊天记录文件，
调用关系：被processing_server_message调用
参数：buf,传入登录用户ID
返回值：返回-1 打开失败
        返回fd 返回成功打开的文件描述符
***********************************************************************/
int open_client_chat_logs_file(char *buf)
{
    char name[40];                   //记录打开文件名字的字符串
    int len_ID = strlen(buf);        //登录用户的ID
    
    /* 将name置为 ./client_chat_logs/(用户ID)\0   */
    strncpy(name,"./client_chat_logs/",19);            
    strncpy(name + 19,buf,len_ID);
    strncpy(name + 19 + len_ID, ".txt", 4);
    *(name + 19 + len_ID + 4) = '\0';
	int fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)          //出错处理
	{
		perror("open ./chat_record.txt");
		return -1;
	}
    return fd;    //返回文件描述符
}

/***********************************************************************
文件名：print_login_status
文件功能：输出登录状态
调用关系：被processing_server_message调用
参数：p_server,记录用户登录状态，用户ID
返回值：无
***********************************************************************/
void print_login_status(link_msg p_server)
{
    int login_status = *(p_server->msg) - '0';
    
    /* 输出用户自身登录状态 */
    if (p_server->feedback == 0)
    {
        if (login_status == ON_LINE)
            printf("您的登录状态为 上线\n");
        if (login_status == STEALTH)
            printf("您的登录状态为 隐身\n");
        if (login_status == LEAVE)
            printf("您的登录状态为 离开\n");
        if (login_status == NO_DISTURB)
            printf("您的登录状态为 免扰\n");
        return;
    }
    
    /* 输出其他用户登录状态 */
    if (p_server->feedback == 1)
    {
        if (login_status == ON_LINE)
            printf("%s 的登录状态为 上线\n",p_server->src_ID);
        if (login_status == STEALTH)
            printf("%s 的登录状态为 隐身\n",p_server->src_ID);
        if (login_status == LEAVE)
            printf("%s 的登录状态为 离开\n",p_server->src_ID);
        if (login_status == NO_DISTURB)
            printf("%s 的登录状态为 免扰\n",p_server->src_ID);
        return;
    }
}

/***********************************************************************
文件名：current_time
文件功能：输出当前时间
调用关系：被processing_server_message调用
参数：无
返回值：无
***********************************************************************/
void current_time(void)
{
    struct tm *ptr; 
    time_t localTime; 
    char str[80]; 
    localTime=time(NULL); 
    ptr=localtime(&localTime); 
    //strftime(str,100," %F %X",ptr); 
    strftime(str,100," %X",ptr);       //将当前时间保存至字符数组str中
    printf("%s\n",str);                //打印当前时间
}

/***********************************************************************
文件名：return_current_time
文件功能：返回当前时间
调用关系：被processing_server_message调用
参数：储存当前时间的字符串
返回值：无
***********************************************************************/
void return_current_time(char *buf)
{
    struct tm *ptr; 
    time_t localTime; 
    localTime=time(NULL); 
    ptr=localtime(&localTime); 
    strftime(buf,100," %X",ptr);       //将当前时间保存至字符数组buf中
}

/***********************************************************************
文件名：processing_server_message
文件功能：处理来自服务器的各种信息
调用关系：被server.c文件中的main函数调用
参数：sockfd,用户所在客户端与服务器间的套接字
      p_server,记录用户ID，接收方ID，消息内容，消息类型，反馈值等信息
      fd,打开消息记录文件
返回值：各种信息枚举值
***********************************************************************/
int processing_server_message(int sockfd,link_msg p_server,int fd)
{
    switch (p_server->msg_type)
    {
        /* 输出在线ID  */
        case LOOK_ON_LINE:
        {
            printf("在线ID如下 ： \n");
            printf("%s\n",p_server->msg);       //输出所有在线ID
            break;
        }
        /* 将当前ID下线，返回主页面 */
        case HOME:
        {
            if (p_server->feedback == 0)
            {
                printf("您本次登录的ID已下线，返回主页\n");
                return HOME;
            }
            if (p_server->feedback == 1)
            {
                printf("%s 已下线\n",p_server->src_ID);
                break;
            }
        }
        /* 重新选择登录状态成功后显示当前自己或其他用户的登录状态 */
        case RELOGIN:
        {
            print_login_status(p_server);
            return RELOGIN;
        }
        /* 管理员禁言用户 */
        case SILENCE:
        {
            /* 向管理员反馈禁言用户未注册，禁言失败 */
            if (p_server->feedback == 0)   
            {
                printf("您禁言的用户 %s 没有注册\n",p_server->dest_ID);
                return SILENCE;
            }
            /* 向管理员反馈禁言用户未登录，禁言失败 */
            if (p_server->feedback == 1)   //管理员反馈禁言信息
            {
                printf("您禁言的用户 %s 没有登录\n",p_server->dest_ID);
                return SILENCE;
            }
            /* 向管理员反馈禁言用户已成功，输出禁言的状态 */
            if (p_server->feedback == 2)   //管理员反馈禁言信息
            {
                if ((*p_server->msg - '0') == 1)        //silence置1表示禁言 -1为正常
                    printf("您已成功禁言 %s\n",p_server->dest_ID);
                else
                    printf("您已成功解除对 %s 的禁言\n",p_server->dest_ID);
                return SILENCE;
            }
            /* 向普通用户反馈您已被管理员禁言，输出禁言的状态 */
            if (p_server->feedback == 3)  //指定用户反馈禁言信息
            {
                if ((*p_server->msg - '0') == 1)        //silence置1表示禁言 -1为正常
                    printf("您已被管理员 %s 禁言\n",p_server->src_ID);
                else
                    printf("您已被管理员 %s 解除禁言\n",p_server->src_ID);
                return SILENCE;
            }
            /* 向其他用户反馈指定用户已被管理员禁言，输出禁言的状态 */
            if(p_server->feedback == 4)                     //其他在线用户反馈禁言信息
            {
                if ((*p_server->msg - '0') == 1)
                    printf("%s 已被 %s 禁言\n",p_server->dest_ID, p_server->src_ID);
                else
                    printf("%s 已被 %s 解除禁言\n",p_server->dest_ID, p_server->src_ID);
                return SILENCE;
            }
            if (p_server->feedback == 5)
            {
                printf("要禁言的用户 %s 为管理员\n",p_server->dest_ID);
                printf("您不是本聊天室作者，无踢出管理员权限\n");
                return KICKED_OUT;
            }
        }
        /* 处理私聊信息 */
        case WHISPER:
        {
            /* 向私聊发起方反馈接收方登录状态，判断是否可以接收信息  */
            if (p_server->feedback == NO_DISTURB)
            {
                printf("%s 用户状态为免扰,无法接收到您发送的消息\n",
                        p_server->whisper_receiver_ID);
                printf("输入 /- 可以退出私聊界面\n");
                return WHISPER;
            }
            if (p_server->feedback == DOWNLINE)
            {
                printf("%s 已下线,无法接收到您发送的消息\n",
                        p_server->whisper_receiver_ID);
                printf("输入 /- 可以退出私聊界面\n");
                return WHISPER;
            }
            if (p_server->feedback == LEAVE)
            {
                printf("%s 已离开,可能无法及时回复您发送的消息\n",
                        p_server->whisper_receiver_ID);
                //printf("输入 /- 可以退出私聊界面\n");
            }

            /* 向私聊发送方反馈私聊发送成功，并将私聊信息写入私聊发起方聊天记录文件 */
            if (p_server->feedback == 2)          //向私聊发送方回复私聊发送成功
            {
                printf("您已向 %s 发送消息:\n",p_server->whisper_receiver_ID);
                fprintf(stdout,"%s\n",p_server->msg);
                printf("您正处在私聊界面中，输入 /- 可以退出私聊界面\n");
                
                /* 将发送成功的信息写入聊天记录文件 */
                char buf[10];
                return_current_time(buf);
                Write(fd, "\n", 1);
                Write(fd, "send", 4);
                Write(fd, " (whisper)", 10);              
                Write(fd, buf, 9);
                Write(fd, "\n\t", 2);
                Write(fd, "to ", 3);
                Write(fd, p_server->whisper_receiver_ID, strlen(p_server->whisper_receiver_ID));
                Write(fd, " / ", 3);
                Write(fd, p_server->msg, strlen(p_server->msg));
                Write(fd, "\n", 1);
            }
            /* 向私聊接收方反馈成功接收私聊信息 */
            if (p_server->feedback == 1)
            {
                /* 判断是否为特殊表情，名字替换 */
                if ((strncmp(p_server->msg, ":)", 2) == 0)
                        && (strlen(p_server->msg) == 2))
                {
                    printf("\n%s (私聊) ",p_server->src_ID);
                    current_time();
                    printf("向您做了个笑脸\n");
                }
                else if ((strncmp(p_server->msg, ":(", 2) == 0)
                        && (strlen(p_server->msg) == 2))
                {
                    printf("\n%s (私聊) ",p_server->src_ID);
                    current_time();
                    printf("向您做了个哭脸\n");
                }
                else if ((strncmp(p_server->msg, "welcome", 7) == 0)
                        && (strlen(p_server->msg) == 7))
                {
                    printf("\n%s (私聊) ",p_server->src_ID);
                    current_time();
                    printf("%s大侠,  欢迎您来到熠飞聊天室\n",p_server->whisper_receiver_ID);
                }

                /* 私聊接收方输出普通私聊信息 */
                else
                {
                    printf("\n%s(私聊) ",p_server->src_ID);
                    current_time();
                    printf("%s\n",p_server->msg);
                }
                
                /* 将收到的私聊信息写入接收方聊天记录文件 */
                char buf[10];
                return_current_time(buf);
                Write(fd, "\n", 1);
                Write(fd, "receive", 7);
                Write(fd, " (whisper)", 10);              
                Write(fd, buf, 9);
                Write(fd, "\n\t", 2);
                Write(fd, "from ", 5);
                Write(fd, p_server->src_ID, strlen(p_server->src_ID));
                Write(fd, " / ", 3);
                Write(fd, p_server->msg, strlen(p_server->msg));
                Write(fd, "\n", 1);
            }
            return WHISPER;
        }
        /* 处理群聊信息  */
        case GROUP:
        {
            /* 向群聊发起方反馈群聊发送情况 */
            if (p_server->feedback == 1)
            {
                /* 如果聊天室内没有用户在线，反馈群聊发送失败信息 */
                if (strlen(p_server->msg) == 0)
                {
                    printf("聊天室内没有其他用户在线\n");
                    printf("您的群聊消息发送失败\n");
                    return GROUP;
                }
                
                /* 群聊消息发送成功后，向群聊发送方反馈接收方ID列表，群聊消息内容 */
                
                char buf_msg[LEN_MSG];             //保存群聊消息的字符串缓冲区
                char *receiver_ID;         //保存接收用户ID
                int len_total = strlen(p_server->msg);
                
                int i = 0;
                while (*(p_server->msg + i) != '\0')
                {
                    i++;
                }

                strcpy(buf_msg, p_server->msg + i + 1);
                int len_receiver_ID = i + 1;
                receiver_ID = (char *)malloc(len_receiver_ID);
                
                i = 0;
                while (*(p_server->msg + i) != '\0')
                {
                    if (*(p_server->msg + i) != '\n')
                        *(receiver_ID + i) = *(p_server->msg + i);
                    else
                        *(receiver_ID + i) = ' ';
                    i++;
                }
                *(receiver_ID + i) = '\0';
                
                /* 输出接收方ID列表，群聊消息 */
                printf("用户 ： \n");
                printf("%s",p_server->msg);       //群聊发起者输出所有接收群聊消息ID
                printf("成功接收到您发送的信息:\n");
                fprintf(stdout,"%s\n",buf_msg);
                
                /* 将发送成功的信息写入发送方聊天记录文件 */
                char buf[10];
                return_current_time(buf);
                Write(fd, "\n", 1);
                Write(fd, "send", 4);
                Write(fd, " (group)", 8);
                Write(fd, buf, 9);
                Write(fd, "\n\t", 2);
                Write(fd, "to ", 3);
                Write(fd, receiver_ID, len_receiver_ID - 1);
                Write(fd, "\n\t", 2);
                Write(fd, buf_msg, strlen(buf_msg));
                Write(fd, "\n", 1);
                
                return GROUP;
            }
            
            /* 向群聊接收方发送群聊消息 */
            /* 判断群聊消息是否为特殊符号或者ID替换 */
            if ((strncmp(p_server->msg, ":)", 2) == 0)
                    && (strlen(p_server->msg) == 2))
            {
                printf("\n%s (群聊) ",p_server->src_ID);
                current_time();
                printf("向大家做了个笑脸\n");
            }
            else if ((strncmp(p_server->msg, ":(", 2) == 0)
                    && (strlen(p_server->msg) == 2))
            {
                printf("\n%s (群聊) ",p_server->src_ID);
                current_time();
                printf("向大家做了个哭脸\n");
            }
            else if ((strncmp(p_server->msg, "welcome", 7) == 0)
                    && (strlen(p_server->msg) == 7))
            {
                printf("\n%s (群聊) ",p_server->src_ID);
                current_time();
                printf("%s大侠,  欢迎您来到熠飞聊天室\n",p_server->whisper_receiver_ID);
            }
            /* 向群聊接收方发送普通群聊消息 */
            else
            {
                printf("\n%s(群聊) ",p_server->src_ID);
                current_time();
                printf("%s\n",p_server->msg);
            }
            
            /* 将群聊接收方收到的群聊信息写入接收方聊天记录文件 */
            char buf[10];
            return_current_time(buf);
            Write(fd, "\n", 1);
            Write(fd, "receive", 7);              
            Write(fd, " (group)", 8);
            Write(fd, buf, 9);
            Write(fd, "\n\t", 2);
            Write(fd, "from ", 5);
            Write(fd, p_server->src_ID, strlen(p_server->src_ID));
            Write(fd, " / ", 3);
            Write(fd, p_server->msg, strlen(p_server->msg));
            Write(fd, "\n", 1);
            return GROUP;
        }
        /* 处理管理员踢人信息 */
        case KICKED_OUT:
        {
            /* 向管理员反馈踢出的目标ID未注册 */
            if (p_server->feedback == 0)
            {
                printf("您踢出的用户 %s 没有注册\n",p_server->dest_ID);
                return KICKED_OUT;
            }
            /* 向管理员反馈踢出的目标ID未登录 */
            if (p_server->feedback == 1)
            {
                printf("您踢出的用户 %s 不在线\n",p_server->dest_ID);
                return KICKED_OUT;
            }
            /* 向管理员反馈已成功将目标ID踢出聊天室 */
            if (p_server->feedback == 2)
            {
                printf("您已成功踢出 %s\n",p_server->dest_ID);
                return KICKED_OUT;
            }
            /* 将被踢出ID反馈您已被管理员踢出聊天室,并返回主页界面 */
            if (p_server->feedback == 3)
            {
                printf("您已被管理员 %s 踢出聊天室\n",p_server->src_ID);
                return HOME;
            }
            /* 将其他用户反馈目标用户已被管理员踢出聊天室 */
            if (p_server->feedback == 4)                     
            {
                printf("%s 已被 %s踢出聊天室\n",p_server->dest_ID,p_server->src_ID);
                return KICKED_OUT;
            }
            if (p_server->feedback == 5)
            {
                printf("要踢出目标的用户 %s 为管理员\n",p_server->dest_ID);
                printf("您不是本聊天室作者，无踢出管理员权限\n");
                return KICKED_OUT;
            }
        }
        /* 管理员关闭服务器以及所有客户端 */
        case CLOSE:
        {
            int second = p_server->feedback;                           //关闭服务器缓冲秒数
            while (second)
            {
                printf("距离服务器和所有客户端关闭还有 %d 秒\n",--second);
                sleep(1);
            }
            printf("服务器以及所有客户端已经关闭\n");
            exit(0);
        }
        case ADDING_ADMIN:
        {
            if (p_server->feedback == 0)
            {
                printf("您添加的管理员ID未注册\n");
                return ADDING_ADMIN;
            }
            /* 向作者反馈管理员设置情况  */
            if (p_server->feedback == 1)
            {
                if (*p_server->msg - '0' == 1)
                {
                    printf("您已成功设置 %s 为管理员,\n",p_server->dest_ID);
                }
                else if (*p_server->msg - '0' == -1)
                {
                    printf("您已成功撤销 %s 的管理员资格\n",p_server->dest_ID);
                }
            }

            /* 向目标用户反馈管理员设置情况  */
            if (p_server->feedback == 2)
            {
                if (*p_server->msg - '0' == 1)
                {
                    printf("您已被 %s 成功设置为管理员,\n",p_server->src_ID);
                }
                else if (*p_server->msg - '0' == -1)
                {
                    printf("您已被作者 %s 撤销管理员资格\n",p_server->src_ID);
                }
            }
            
            /* 向其他用户反馈管理员设置情况  */
            if (p_server->feedback == 3)
            {
                if (*p_server->msg - '0' == 1)
                {
                    printf("%s 已被作者 %s 成功设置为管理员,\n",
                            p_server->dest_ID, p_server->src_ID);
                }
                else if (*p_server->msg - '0' == -1)
                {
                    printf("%s 已被作者 %s 撤销管理员资格,\n",
                            p_server->dest_ID, p_server->src_ID);
                }
            }
            break;
        }
        case ADMIN_APPLY:
        {
            if (p_server->feedback == 3)
            {
                printf("用户 %s 已成功申请成为管理员\n", p_server->src_ID);
                return ADMIN_APPLY;
            }
            if (p_server->feedback == 2)
            {
                printf("您已被禁言，无法申请管理员权限\n");
                return ADMIN_APPLY;
            }
            if (p_server->feedback == 1)
            {
                printf("恭喜您已成功申请成为管理员\n");
                printf("管理员特殊权限已为您全面开启\n");
                return ADMIN_APPLY;
            }
            else
            {
                printf("您申请管理员权限失败,密码不符合，请与服务器管理员联系\n");
                return ADMIN_APPLY;
            }
        }
        default :
            ;
    }
}
