/* 文件名 ： home_page.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "home_page.h"
#include "processing_terminal_message.h" 

void close_prompt(void)
{
	printf("            熠飞聊天室客户端已关闭                \n");
    printf("           感谢您对熠飞聊天室的支持               \n");
    printf("我们将以最诚挚的服务为您创造更方便更快捷的聊天环境\n");
    printf("                   ！再见了！                     \n");
}

char *cancel_spaces(char *src)
{
    int len = mystrlen(src);
    char buf[LEN_MSG];
    int len_spaces = 0;
    while (*(src + len_spaces) == ' ')
    {
        len_spaces++;
    }
    strncpy(buf,src + len_spaces,len - len_spaces + 1);
    
    len--;
    while (*(src + len) == ' ')
    {
        *(src + len) = '\0';
        len--;
    }
    //*(src + len + 1) = '\0';a
    *(buf + len - len_spaces + 1) = '\0';
    strncpy(src,buf,len - len_spaces + 2) ;
}

int user_command(char *buf)
{
    int len = strlen(buf);
    if (len != 1)
        return -1;
    if (*buf < '0' || *buf > '2')
        return -1;
    if (strncmp(buf,"0",1) == 0)
    {
        return 0;
    }
    if (strncmp(buf,"1",1) == 0)
    {
        return 1;
    }
    if (strncmp(buf,"2",1) == 0)
    {
        return 2;
    }
}

int mystrlen(char *buf)
{
    int len = 0;
    while (buf[len] != '\n')
    {
        len++;
    }
    return len;
}

void health_tips(void)
{
    printf("\n********您已开启客服端********\n");
    printf("\n         温馨小贴士           \n");
    printf("\n        适度聊天益脑          \n");
    printf("\n        沉迷聊天伤身          \n");
    printf("\n        合理安排时间          \n");
    printf("\n        享受健康生活          \n");
    printf("\n******************************\n");    
}

void home_page(void)
{
    printf("\n****************************************\n");
    printf("\n< 熠飞聊天室欢迎您的使用，祝您聊天愉快 >\n");
    printf("\n<   请输入数字快捷键选择您需要的服务   >\n");
    printf("\n<             注册  ->  请按0          >\n");
    printf("\n<             登录  ->  请按1          >\n");
    printf("\n<             退出  ->  请按2          >\n");
    printf("\n****************************************\n");
}

/******************************************************************
函数名：user_register
函数功能：用户注册ID号
输入参数：sockfd，为与服务器连接后进行通信的描述符
          p，为发送给服务器的消息结构体的指针
返回值：            
******************************************************************/
int user_register(int sockfd,link_msg p)
{
    char buf_password[40] = {0};
    int len_password, len_password2;       //从终端读取数组的位数
    char flag;
    int len_ID = 0;
    
register_ID:
    memset(p->msg, 0, sizeof(p->msg));                   /*清空p->msg */
    printf("请输入您要注册的 6 - 16位 帐号  或  输入 1 返回主页：\n");
    Read(STDIN_FILENO, p->msg, USER_DATA_LEN);          /* 输入用户ID */
    cancel_spaces(p->msg);
    len_ID = strlen(p->msg);
    if ((strncmp(p->msg,"1",1) == 0) && (len_ID == 1))   //判断是否为返回主页
        return RETURN_HOME_PAGE;
    
    if (len_ID == 0)
    {
        printf("密码不能为空，请重新输入\n");
        goto register_password;
    }
    
    if (len_ID < 6 || len_ID > 16)
    {
        printf("您输入的ID号位数不符合要求，请重新输入.\n");
        goto register_ID;
    }
    
    
    p->msg_type = REG_ID_JUDGE;       //将帐号判断标志写入msg_type
    Write(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    Read(sockfd, &flag, 1);
    printf("flag : %c\n",flag);
    
    if (flag == '1')
    {
        printf("此ID已被使用，请重新注册申请ID\n");
        goto register_ID;
    }
    else if (flag == '0')
    {
        printf("此ID未被使用\n");
        *(p->msg + len_ID) = '-';
        goto register_password;
    }
register_password:
    printf("请输入您要注册的 6 - 16位 密码  或 输入 1 返回主页面  或输入 2 重新注册ID\n");
    memset(p->msg + len_ID + 1, 0, sizeof(p->msg + len_ID + 1));
    Read(STDIN_FILENO, p->msg + len_ID + 1, 40);
    cancel_spaces(p->msg + len_ID + 1);
    len_password = strlen(p->msg + len_ID + 1);
    
    if (len_password == 0)
    {
        printf("密码不能为空，请重新输入\n");
        goto register_password;
    }
    
    if ((strncmp(p->msg + len_ID + 1,"1",1) == 0) && (len_password == 1))   //判断是否为返回主页
        return RETURN_HOME_PAGE;
    
    if ((strncmp(p->msg + len_ID + 1,"2",1) == 0) && (len_password == 1))   //判断是否为重新注册
        goto register_ID;
    
    if (len_password < 6 || len_password > 16)
    {
        printf("您输出的密码位数不符合要求，请重新输入\n");
        goto register_password;
    }

user_password2:
    printf("请再次输入密码，以进行确认  或  输入1返回主页  或输入2重新注册密码\n");
    memset(buf_password, 0, sizeof(buf_password));
    Read(STDIN_FILENO, buf_password, 40);    //改
    cancel_spaces(buf_password);             //改
    len_password2 = strlen(buf_password);    //改
    
    if (len_password2 == 0)
    {
        printf("密码不能为空，请重新输入\n");
        goto user_password2;
    }
    
    if ((strncmp(buf_password,"1",1) == 0) && (len_password2 == 1))   //判断是否为返回主页
        return RETURN_HOME_PAGE;
    
    if ((strncmp(buf_password,"2",1) == 0) && (len_password2 == 1))   //判断是否为返回主页
        goto register_password;
    
    if (len_password2 < 6 || len_password2 > 16)
    {
        printf("您输出的密码位数不符合要求，请重新输入\n");
        goto user_password2;
    }
    /* 对用户密码进行校验 */     
    if ((strncmp(p->msg + len_ID + 1, buf_password, len_password2) != 0) 
            || (len_password != len_password2))        
    {
        printf("您输入的密码与上一次输入的不符\n");
        goto user_password2;
    }
    *(p->msg + len_ID + len_password2 + 1) = '\0';
    printf("msg : %s\n",p->msg);
    p->msg_type = REG;       //将帐号判断标志写入msg_type
    Write(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    printf("恭喜您成功注册为熠飞聊天室会员\n");
}

/******************************************************************
函数名：user_login
函数功能：用户登录 ID 密码
输入参数：sockfd，为与服务器连接后进行通信的描述符
          p，为发送给服务器的消息结构体的指针
返回值：            
******************************************************************/
char user_login(int sockfd, link_msg p)
{
	int len_ID,len_password,len_status;						/* 从终端键盘读取数据 */
	char flag;	                                    /* 返回服务器端发送来的登录结果信息 */  
login_ID:
	printf("请输入您要登录的 6-16位 ID号  或  输入 1 返回主页 ： \n");
    memset(p->msg, 0, sizeof(p->msg));                   /*清空p->msg */
	Read(STDIN_FILENO, p->msg, USER_DATA_LEN);          /* 输入用户ID */
    
    cancel_spaces(p->msg);
    len_ID = strlen(p->msg);
    
    if (len_ID == 0)
    {
        printf("ID不能为空，请重新输入\n");
        goto login_ID;
    }
    
    if ((strncmp(p->msg,"1",1) == 0) && (len_ID == 1))   //判断是否为返回主页
        return RETURN_HOME_PAGE;
    
    if (len_ID < 6 || len_ID > 16)
    {
        printf("您输入的ID号位数不符合要求，请重新输入.\n");
        goto login_ID;
    }
    printf("输入格式正确\n");
    p->msg_type = LOGIN_ID_JUDGE;       //将帐号判断标志写入msg_type
    Write(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    
    Read(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    
    if (p->feedback == 0)
    {
        printf("此ID没有注册，请重新登录其他ID\n");
        goto login_ID;
    }
    else if (p->feedback == 1)
    {
        printf("此ID已被登录，请选择其他ID登录\n");
        goto login_ID;
    }
    else if (p->feedback == 2)
    {
        printf("此ID曾被管理员踢出聊天室\n");
        int wait_time = *(p->msg) - '0';
        printf("请注意文明用语，等待%d分钟后再登录\n",wait_time);
        goto login_ID;
    }
    else
    {
        printf("此ID可以登录\n");
        *(p->msg + len_ID) = '\0';
        goto login_password;
    }
login_password:
	printf("请输入您的密码  或  输入 1 返回主页  或  输入 2 重新登录其他帐号 : \n");
    
    //len_password = Read(STDIN_FILENO, p->msg + len_ID + 1, 40) - 1;
    Read(STDIN_FILENO, p->msg + len_ID + 1, 40);
    
    cancel_spaces(p->msg + len_ID + 1);
    len_password = strlen(p->msg + len_ID + 1);
    
    if (len_password == 0)
    {
        printf("密码不能为空，请重新输入\n");
        goto login_password;
    }
    
    if ((strncmp(p->msg + len_ID + 1,"1",1) == 0) && (len_password == 1))   //判断是否为返回主页
        return RETURN_HOME_PAGE;
    
    if ((strncmp(p->msg + len_ID + 1,"2",1) == 0) && (len_password == 1))   //判断是否为返回主页
        goto login_ID;

    if (len_password < 6 || len_password > 16)
    {
        printf("您输出的密码位数不符合要求，请重新输入\n");
        goto login_password;
    }
    
    p->msg_type = LOGIN_PASSWORD_JUDGE;       //将帐号判断标志写入msg_type
    Write(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    
    Read(sockfd, &flag, 1);
    if (flag == '1')
    {
        printf("密码输入正确\n");
        *(p->msg + len_ID + len_password + 1) = '-';
        goto login_status;
    }
    else if (flag == '0')
    {
        printf("密码输入错误\n");
        goto login_password;
    }
    
login_status:    
	printf("请输入您的登录状态\n");
    printf("    上线请按 1    \n");
    printf("    隐身请按 2    \n");
    printf("    离开请按 3    \n");
    printf("    免扰请按 4    \n");
    Read(STDIN_FILENO, p->msg + len_ID + len_password + 2, 40);
    cancel_spaces(p->msg + len_ID + len_password + 2);
    len_status = strlen(p->msg + len_ID + len_password + 2);
    
    if (len_status != 1)
    {
        printf("您输入内容位数不符\n");
        goto login_status;
    }
    
    int user_status = *(p->msg + len_ID + len_password + 2) - '0';
    if (user_status < 1 || user_status > 4)
    {
        printf("您输入的登录状态错误\n");
        goto login_status;
    }
    
    /*//判断是否为返回主页
    if ((strncmp(p->msg + len_ID + len_password + 2,"1",1) == 0) && (len_status == 1))   
        return RETURN_HOME_PAGE;
    
    //判断是否为重新登录
    if ((strncmp(p->msg + len_ID + len_password + 2,"2",1) == 0) && (len_status == 1))   
        goto login_status;*/
    
    strncpy(p->src_ID, p->msg, len_ID);     //将登录成功的ID写入src_ID中
    *(p->src_ID + len_ID) = '\0';
    
    p->msg_type = LOG;       //将帐号判断标志写入msg_type
    Write(sockfd, p, sizeof(*p));                           /* 将用户ID和密码传递给服务器 */   
    printf("登录成功，欢迎您使用熠飞聊天室\n");
    return;
}

void login_processing(int sockfd,link_msg p)
{
    char command[40];
    int flag;

begin:
    home_page();
    Read(0,command,40);
    cancel_spaces(command);
    switch(user_command(command))
    {
        case REGISTER:
        {
            printf("注册提示\n");
            user_register(sockfd,p);
            goto begin;
        }
        case LOGIN:
        {
            printf("登录提示\n");
            flag = user_login(sockfd,p);
            if (flag == RETURN_HOME_PAGE)
                goto begin;
            break;
        }
        case EXIT:
        {
            if(atexit(close_prompt)!=0)
                printf("can't register myexit2\n");
            exit(0);
        }
        case -1:
        {
            printf("输入格式不对,请重新输入\n");
            goto begin;
        }
        default : 
            ;
    }
}

