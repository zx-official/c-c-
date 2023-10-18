/*文件名 ： home_page.h*/

enum user_register{REG_ID_JUDGE, REG, LOGIN_ID_JUDGE, LOGIN_PASSWORD_JUDGE,LOG};
enum return_flag{RETURN_HOME_PAGE};
enum operating_instructions{REGISTER,LOGIN,EXIT};
enum login_status{DOWNLINE, ON_LINE, STEALTH, LEAVE, NO_DISTURB};

#define LEN_MSG 1000               //消息的最大长度
#define USER_DATA_LEN 40         //用户 帐号 密码 位数的最大总值

typedef struct user_msg* link_msg;
struct user_msg
{
    char src_ID[17];                //登录用户本人ID
    char dest_ID[17];               //目标ID(用户除私聊以外的其他通信)
    char whisper_receiver_ID[17];   //私聊接收方ID
    char msg[LEN_MSG];              //记录消息长度
    int msg_type;                   //消息类型
    int feedback;                   //命令反馈信息
};

//void msg_processing(int sockfd,char* buf,link_msg p);
void login_processing(int socket,link_msg p);
int user_command(char *buf);
void home_page(void);
int mystrlen(char *buf);
int user_register(int socket,link_msg p);
char user_login(int sockfd, link_msg p);
void health_tips(void);
char *cancel_spaces(char *src);
void close_prompt(void);
