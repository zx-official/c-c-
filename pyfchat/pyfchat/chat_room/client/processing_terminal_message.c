/***************************************************************************
文件名：processing_terminal_message.c()
文件功能:处理终端键盘上读取出的数据内容
调用关系:被client.c文件中的main函数调用
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "home_page.h"
#include "processing_terminal_message.h"

/************************************************************************
函数名：cancel_judge_mark
功能描述：删除信息类型标志位(删除有效信息的前两位) 
调用关系：被inquire_msg_type调用
参数：传入从终端读入的各种信息
返回值：无
************************************************************************/
void cancel_judge_mark(char *src)
{
    int len = strlen(src);
    char buf[LEN_MSG];
    strncpy(buf,src + 2,len - 1);
    *(buf + len - 2) = '\0';
    strncpy(src, buf, len);
}

/************************************************************************
函数名：cancel_msg_spaces
功能描述：删除从终端读入信息的前后无效空格
调用关系：被inquire_msg_type调用
参数：传入从终端读入的各种信息
返回值：无
************************************************************************/
void cancel_msg_spaces(char *src)
{
    int len = strlen(src);
    int i = 0;
    while(*(src + i) == ' ')
    {
        i++;
    }
    strncpy(src, src + i, len - i);
    *(src + len - i) = '\0';
}

/************************************************************************
函数名：inquire_msg_type
功能描述：查询消息类型,返回消息标志
调用关系：被processing_terminal_message调用
参数：传入从终端读入的各种信息
返回值：返回查询信息的标志
************************************************************************/
char inquire_msg_type(int sockfd,link_msg p_terminal)
{
    int len_msg = strlen(p_terminal->msg);                                   //消息长度
    int len_dest_ID = strlen(p_terminal->dest_ID);                           //接收方ID长度
    int len_src_ID = strlen(p_terminal->src_ID);                             //发送方ID长度
    int len_whisper_receiver_ID 
        = strlen(p_terminal->whisper_receiver_ID);                           //发送方ID长度
    
    /* 查询已登录ID */
    if ((strncmp(p_terminal->msg,"online/",7) == 0) && (len_msg == 7))
    {
        return LOOK_ON_LINE;
    }
    
    /* 查询帮助界面 */
    if ((strncmp(p_terminal->msg,"help/",5) == 0) && (len_msg == 5))
        return HELP;
    
    /* 返回主页 */
    if ((strncmp(p_terminal->msg,"home/",5) == 0) && (len_msg == 5))
        return HOME;
    
    /* 申请私聊，加入私聊接收方 */
    if (strncmp(p_terminal->msg,"+/",2) == 0)
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将消息删除空格
        return WHISPER_JUDGE;
    }

    /* 解除私聊，删除私聊接收方 */
    if ((strncmp(p_terminal->msg,"-/",2) == 0) 
            && (len_msg == 2) 
            && (len_whisper_receiver_ID != 0))
        return EXIT_WHISPER;
    
    /* 如果未建立私聊关系，则解除私聊无效 */
    if ((strncmp(p_terminal->msg,"-/",2) == 0) 
            && (len_msg == 2) 
            && (len_whisper_receiver_ID == 0))
    {
        printf("您未建立私聊关系，解除私聊操作无效\n");
        return -1;
    }
    
    /* 改变用户登录状态 */
    if ((strncmp(p_terminal->msg,"c/",2) == 0) && (len_msg == 3))
        return RELOGIN;
    
    /* 发送群聊信息 */
    if (strncmp(p_terminal->msg,"g/",2) == 0)
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将群聊消息删除空格
        return GROUP;
    }

    /* 作者踢人 */
    if (strncmp(p_terminal->msg,"k/",2) == 0 
            && (strncmp(p_terminal->src_ID, "pyfadmin",8) == 0)
            && (len_src_ID == 8))          
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将踢出ID删除空格
        return KICKED_OUT;
    }
    
    /* 管理员踢人 */
    if ((strncmp(p_terminal->msg,"k/",2) == 0)
            && ((len_src_ID != 8)
            || (strncmp(p_terminal->src_ID, "pyfadmin",8) != 0)))
    {
        if (administrator_judgment(sockfd,p_terminal) == 1)
        {
            cancel_judge_mark(p_terminal->msg);
            cancel_msg_spaces(p_terminal->msg);         //将聊天消息删除空格
            return KICKED_OUT;
        }
        else
        {
            printf("对不起，您不是管理员，请申请成功后再使用管理员权限\n");
            return -1;
        }
    }

    /* 作者关闭服务器 */
    if ((strncmp(p_terminal->msg,"close/",6) == 0) 
            && (len_msg == 6) 
            && (strncmp(p_terminal->src_ID, "pyfadmin",8) == 0)
            && (len_src_ID == 8))
        return CLOSE;

    /* 管理员关闭服务器 */
    if ((strncmp(p_terminal->msg,"close/",6) == 0)
            && (len_msg == 6)
            && ((len_src_ID != 8)
            || (strncmp(p_terminal->src_ID, "pyfadmin",8) != 0)))
    {
        if (administrator_judgment(sockfd,p_terminal) == 1)
        {
            return CLOSE;
        }
        else
        {
            printf("对不起，您不是管理员，请申请成功后再使用管理员权限\n");
            return -1;
        }
    }
    
    /* 作者对用户禁言 */
    if ((strncmp(p_terminal->msg,"s/",2) == 0) 
            && (len_src_ID == 8)
            && (strncmp(p_terminal->src_ID, "pyfadmin",8) == 0))
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将禁言用户删除空格
        return SILENCE;
    }

    /* 管理员对用户禁言 */
    if ((strncmp(p_terminal->msg,"s/",2) == 0) 
            && ((len_src_ID != 8)
            || (strncmp(p_terminal->src_ID, "pyfadmin",8) != 0)))
    {
        if (administrator_judgment(sockfd,p_terminal) == 1)
        {
            cancel_judge_mark(p_terminal->msg);
            cancel_msg_spaces(p_terminal->msg);         //将禁言用户删除空格
            return SILENCE;
        }
        else
        {
            printf("对不起，您不是管理员，请申请成功后再使用管理员权限\n");
            return -1;
        }
    }
    
    /* 普通用户申请成为管理员 */
    if ((strncmp(p_terminal->msg,"a/",2) == 0))
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将聊天消息删除空格
        return ADMIN_APPLY;
    }

    /* 作者设置普通用户为管理员 */
    if ((strncmp(p_terminal->msg, "j/", 2) == 0)
            && (len_src_ID == 8)
            && (strncmp(p_terminal->src_ID, "pyfadmin",8) == 0))
    {
        cancel_judge_mark(p_terminal->msg);
        cancel_msg_spaces(p_terminal->msg);         //将撤销资格ID删除空格
        return ADDING_ADMIN;
    }
    
    if ((strncmp(p_terminal->msg, "j/", 2) == 0)
            && ((len_src_ID != 8)
            || (strncmp(p_terminal->src_ID, "pyfadmin",8) != 0)))
    {
        printf("对不起，您不是本聊天室作者，无法使用添加管理员权限\n");
        return -1;
    }
    
    /* 发送私聊信息 */
    if (len_whisper_receiver_ID != 0)
    {
        cancel_msg_spaces(p_terminal->msg);         //将私聊消息删除空格
        return WHISPER;
    }

    return -2;
}

/************************************************************************
函数名：display_help
功能描述：显示用户帮助界面
调用关系：被processing_terminal_message调用
参数：无
返回值：无
************************************************************************/
void display_help()
{
    printf("**************************所有用户操作指令信息***************************\n");
    printf("* online/             ->  查看在线用户(包括管理员)                      *\n");
    printf("* help/               ->  帮助提示信息                                  *\n"); 
    printf("* home/               ->  退出聊天界面转到主页,并将当前登录ID下线       *\n");
    printf("* +/(对方ID)          ->  建立私聊关系,加入私聊对象  例如 +/panyifei    *\n");
    printf("* -/                  ->  解除私聊关系               例如 -/            *\n");
    printf("* (私聊内容)          ->  进行私聊.                  例如 hello         *\n");
    printf("* g/(群聊内容)        ->  进行群聊                   例如 g/hello       *\n");
    printf("*     (聊天内容) 中输入   :)  为向用户发送笑脸   :(  为向用户发送哭脸   *\n");
    printf("* c/(登录状态)        ->  重新设置登录状态,                             *\n");
    printf("*   c/1上线  c/2隐身  c/3离开  c/4免扰                                  *\n");
    printf("* a/(密码)            ->  普通用户申请为管理员       例如 a/20120808    *\n");
    printf("*************************尊贵的管理员特殊权限如下************************\n");
    printf("* s/(对方ID)          ->  禁言对方ID                 例如   s/panyifei  *\n");
    printf("* j/(对方ID)          ->  作者赋予用户管理员资格     例如 j/panyifei    *\n");
    printf("* 如需要解除禁言状态，或撤销管理员资格，请再次输入相同指令              *\n");
    printf("* k/(对方ID)          ->  将对方用户踢出熠飞聊天室   例如 k/panyifei    *\n");
    printf("* close/              ->  关闭服务器以及所有客户端                      *\n");
    printf("*************************************************************************\n");
}

/************************************************************************
函数名：whisper_judgment
功能描述：用户私聊检验，返回用户是否可以接收私聊信息
调用关系：被processing_terminal_message调用
参数：sockfd,私聊发起者与服务器间的套接字
      p_terminal，记录私聊发起者的ID 私聊接收方ID
返回值：返回私聊接收方接收状态
************************************************************************/
int whisper_judgment(int sockfd,link_msg p_terminal)
{
    int len_ID;
    //printf("您已进入私聊判断界面\n");
    //cancel_judge_mark(p_terminal->msg);
    len_ID = strlen(p_terminal->msg);
    if (len_ID < 6 || len_ID > 16)
    {
        printf("您输入的接收用户ID位数不符\n");
        return;
    }
    memset(p_terminal->whisper_receiver_ID, 0, sizeof(p_terminal->whisper_receiver_ID));
    strcpy(p_terminal->whisper_receiver_ID, p_terminal->msg);

    p_terminal->msg_type = WHISPER_JUDGE;        //加上私聊判断标志
    Write(sockfd, p_terminal, sizeof(*p_terminal));

    Read(sockfd, p_terminal, sizeof(*p_terminal));
    switch(p_terminal->feedback)
    {
        case 0:
        {
            printf("该用户没有注册\n");
            memset(p_terminal->whisper_receiver_ID, 0, sizeof(p_terminal->whisper_receiver_ID));
            break;
        }
        case 1:
        {
            printf("该用户没有上线\n");
            memset(p_terminal->whisper_receiver_ID, 0, sizeof(p_terminal->whisper_receiver_ID));
            break;
        }
        case 2:
        {
            printf("不能向自己发送聊天信息\n");
            memset(p_terminal->whisper_receiver_ID, 0, sizeof(p_terminal->whisper_receiver_ID));
            break;
        }
        case 3:
        {
            printf("该用户不在电脑前,可能无法及时回复您的消息\n");
            break;
        }
        case 4:
        {
            printf("该用户状态为请勿打扰，请稍候再联系\n");
            memset(p_terminal->whisper_receiver_ID, 0, sizeof(p_terminal->whisper_receiver_ID));
            break;
        }
        case 5:
        {
            printf("该用户可以进行聊天\n");
            printf("\n   欢迎您来到私聊界面\n");
            printf("祝您与ID为 %s 的用户聊天愉快\n",p_terminal->whisper_receiver_ID);
            return WHISPER_JUDGE;
        }
    }
}

/************************************************************************
函数名：silence_judgment
功能描述：用户进行聊天前检验是否被禁言
调用关系：被processing_terminal_message调用
参数：sockfd,聊天发起者与服务器间的套接字
      p_terminal，记录聊天发起者的ID 私聊接收方ID
返回值：返回1  已被禁言，无法发送聊天内容
        返回-1 未被禁言，可以发送聊天内容
************************************************************************/
int silence_judgment(int sockfd,link_msg p_terminal)
{
    p_terminal->msg_type = SILENCE_JUDGE;
    Write(sockfd, p_terminal, sizeof(*p_terminal));
    
    Read(sockfd, p_terminal, sizeof(*p_terminal));
    if (p_terminal->feedback == 1)
        return 1;
    else
        return -1;
}

/************************************************************************
函数名：exit_whisper
功能描述：用户关闭私聊状态
调用关系：被processing_terminal_message调用
参数：p_terminal，记录私聊发起者的ID 私聊接收方ID
返回值:无
************************************************************************/
void exit_whisper(link_msg p_terminal)
{
    printf("您已退出与 %s 的私聊\n",p_terminal->whisper_receiver_ID);
    p_terminal->msg_type = EXIT_WHISPER;

    /* 结束私聊状态后删除whisper_receiver_ID */
    memset(p_terminal->whisper_receiver_ID, 0, sizeof(*(p_terminal->whisper_receiver_ID)));
}

/************************************************************************
函数名:change_login_status
功能描述：用户改变登录状态
调用关系：被processing_terminal_message调用
参数：sockfd,申请方与服务器间的套接字
      p_terminal，记录申请发起者的ID 改变的登录状态
返回值:无
************************************************************************/
void change_login_status(int sockfd,link_msg p_terminal)
{
    int login_status;
    cancel_judge_mark(p_terminal->msg);
    login_status = *(p_terminal->msg) - '0';
    if (login_status < 1 || login_status > 4)
    {
        printf("您输入的登录状态不符\n");
        printf("   上线请输入 c/1   \n");
        printf("   隐身请输入 c/2   \n");
        printf("   离开请输入 c/3   \n");
        printf("   免扰请输入 c/4   \n");
        return;
    }
    Write(sockfd, p_terminal, sizeof(*p_terminal));
}

/************************************************************************
函数名:kicked_out_user
功能描述：管理员将指定用户踢出聊天室
调用关系：被processing_terminal_message调用
参数：sockfd,管理员与服务器间的套接字
      p_terminal，记录管理员ID 踢出用户ID
返回值:无
************************************************************************/
void kicked_out_user(int sockfd, link_msg p_terminal)
{
    int len_msg = strlen(p_terminal->msg);
    int len_src_ID = strlen(p_terminal->src_ID);

    if (len_msg < 6 || len_msg > 16)
    {
        printf("您要踢出的用户ID位数不符\n");
        return;
    }
    if ((strcmp(p_terminal->msg, p_terminal->src_ID) == 0) 
            && (len_msg == len_src_ID))
    {
        printf("管理员不能踢自己,若要退出，请输入 home/\n");
        return ;
    }
    if ((strncmp(p_terminal->msg, "pyfadmin", 8) == 0)
            && (len_msg == 8))
    {
        printf("要踢出的目标用户为本聊天室作者，您无此权限\n");
        return;
    }

    p_terminal->msg_type = KICKED_OUT;
    Write(sockfd, p_terminal, sizeof(*p_terminal));
}

/************************************************************************
函数名:silence_user
功能描述：管理员将指定用户禁言
调用关系：被processing_terminal_message调用
参数：sockfd,管理员与服务器间的套接字
      p_terminal，记录管理员ID 禁言用户ID
返回值:无
************************************************************************/
void silence_user(int sockfd,link_msg p_terminal)
{
    int len_msg = strlen(p_terminal->msg);
    int len_src_ID = strlen(p_terminal->src_ID);
    if (len_msg < 6 || len_msg > 16)
    {
        printf("禁言对方的ID位数不符\n");
        return;
    }
    if ((strcmp(p_terminal->msg, p_terminal->src_ID) == 0) 
            && (len_msg == len_src_ID))
    {
        printf("管理员不能禁言自己\n");
        return ;
    }
    if ((strncmp(p_terminal->msg, "pyfadmin", 8) == 0) 
            && (len_msg == 8))
    {
        printf("要禁言的目标用户为本聊天室作者，您无此权限\n");
        return ;
    }

    p_terminal->msg_type = SILENCE;
    Write(sockfd, p_terminal, sizeof(*p_terminal));
}

/************************************************************************
函数名:administrator_judgment
功能描述：管理员身份判断
调用关系：被inquire_msg_type调用
参数：sockfd,管理员与服务器间的套接字
      p_terminal，记录管理员ID
返回值:返回1 是管理员
       返回0 不是管理员
************************************************************************/
int administrator_judgment(int sockfd,link_msg p_terminal)
{
    p_terminal->msg_type = ADMIN_JUDGE;
    Write(sockfd, p_terminal, sizeof(*p_terminal));
    Read(sockfd, p_terminal, sizeof(*p_terminal));
    
    if (p_terminal->feedback == 1)
        return 1;                       //该用户是管理员
    else
        return -1;                      //该用户不是管理员
}

/************************************************************************
函数名:administrator_judgment
功能描述：普通用户申请管理员身份
调用关系：被processing_terminal_message调用
参数：sockfd,申请用户与服务器间的套接字
      p_terminal，记录申请人ID
返回值:无
************************************************************************/
void administrator_application(int sockfd,link_msg p_terminal)
{
    if (strncmp(p_terminal->src_ID, "pyfadmin", 8) == 0)
    {
        printf("      最贵的聊天室作者：潘熠飞\n");
        printf("您永享管理员权限，无须申请管理员权限\n");
        return;
    }
    p_terminal->msg_type = ADMIN_APPLY;
    Write(sockfd, p_terminal, sizeof(*p_terminal));

    /*Read(sockfd, p_terminal, sizeof(*p_terminal));
    if (p_terminal->feedback == 3)
    {
        printf("用户 %s 已成功申请成为管理员\n", p_terminal->src_ID);
    }
    if (p_terminal->feedback == 2)
    {
        printf("您已被禁言，无法申请管理员权限\n");
    }
    else if (p_terminal->feedback == 1)
    {
        printf("恭喜您已成功申请成为管理员\n");
        printf("管理员特殊权限已为您全面开启\n");
    }
    else
    {
        printf("您申请管理员权限失败,密码不符合，请与服务器管理员联系\n");
    }*/
}

void author_adding_administrator(int sockfd,link_msg p_terminal)
{
    strcpy(p_terminal->dest_ID, p_terminal->msg);   
    int len_dest_ID = strlen(p_terminal->dest_ID);
    if (len_dest_ID < 6 || len_dest_ID > 16)
    {
        printf("您要添加的管理员ID位数不符\n");
        return;
    }

    if (strncmp(p_terminal->dest_ID, "pyfadmin", 8) == 0)
    {
        printf("      最贵的聊天室作者：潘熠飞\n");
        printf("您永享管理员权限，无法撤销管理员权限\n");
        return;
    }
    p_terminal->msg_type = ADDING_ADMIN;
    Write(sockfd, p_terminal, sizeof(*p_terminal));
    memset(p_terminal->dest_ID, 0, sizeof(p_terminal->dest_ID));
}

/************************************************************************
函数名:processing_terminal_message
功能描述：处理来自终端键盘输入的各种信息
调用关系：被client.c文件中的mian函数调用
参数：sockfd,客户端与服务器间的套接字
      p_terminal，记录用户ID，接收方ID，消息，消息类型，反馈信息
返回值:各个功能的枚举定义
************************************************************************/
int processing_terminal_message(int sockfd,link_msg p_terminal,int fd)      
{
    switch (inquire_msg_type(sockfd,p_terminal))
    {
        case LOOK_ON_LINE:
        {
            p_terminal->msg_type = LOOK_ON_LINE;
            Write(sockfd, p_terminal, sizeof(*p_terminal));
            return LOOK_ON_LINE;
        }
        case HELP:
        {
            display_help(); 
            p_terminal->msg_type = HELP;
            Write(sockfd, p_terminal, sizeof(*p_terminal));
            return HELP;
        }
        case HOME:
        {
            p_terminal->msg_type = HOME;
            Write(sockfd, p_terminal, sizeof(*p_terminal));
            return HOME;
        }
        case RELOGIN:
        {
            p_terminal->msg_type = RELOGIN;
            change_login_status(sockfd,p_terminal);
            return RELOGIN;
        }
        case WHISPER_JUDGE:       //判断私聊对象，并建立私聊关系
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
                whisper_judgment(sockfd,p_terminal);
            else
                printf("您已被禁言,不能发送任何聊天信息\n");
            return WHISPER_JUDGE;
        }
        case WHISPER:
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
            {
                p_terminal->msg_type = WHISPER;        //加上私聊标志
                //printf("发出了吗？\n");
                Write(sockfd, p_terminal, sizeof(*p_terminal));
            }
            else
                printf("您已被禁言,不能发送任何聊天信息\n");
            return WHISPER;
        }
        case EXIT_WHISPER:
        {
            exit_whisper(p_terminal);
            Write(sockfd, p_terminal, sizeof(*p_terminal));
            return EXIT_WHISPER;
        }
        case GROUP:
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
            {
                p_terminal->msg_type = GROUP;
                Write(sockfd, p_terminal, sizeof(*p_terminal));
            }
            else 
                printf("您已被禁言,不能发送任何聊天信息\n");
            return GROUP;
        }
        case KICKED_OUT:
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
            {
                kicked_out_user(sockfd,p_terminal);
            }
            else
                printf("您已被禁言,不能使用踢人权限\n");
            return KICKED_OUT;
        }
        case CLOSE:
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
            {
                p_terminal->msg_type = CLOSE;
                Write(sockfd, p_terminal, sizeof(*p_terminal));
            }
            else
                printf("您已被禁言,不能使用关闭服务器以及所有客户端权限\n");
            return CLOSE;
        }
        case SILENCE:
        {
            if (silence_judgment(sockfd,p_terminal) != 1)   //没有禁言则发出消息
            {
                silence_user(sockfd,p_terminal);
            }
            else
                printf("您已被禁言,不能使用禁言权限\n");
            return SILENCE;
        }
        case ADMIN_APPLY:
        {
            administrator_application(sockfd,p_terminal);
            return ADMIN_APPLY;
        }
        case ADDING_ADMIN:
        {
            author_adding_administrator(sockfd,p_terminal);
            return ADDING_ADMIN;
        }
        case -2:
            return -2;
        default :
            ;
    }
}

