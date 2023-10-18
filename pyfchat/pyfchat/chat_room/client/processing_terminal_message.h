/* 函数名 processing_terminal_message.h */

/*查看消息类型查询在线用户 帮助  ID下线，回到主页面  重新选择登录状态*/
enum msg_type{LOOK_ON_LINE = 5, HELP, HOME,               RELOGIN};
/*聊天消息类型     建立私聊           进行私聊 退出私聊      群聊   普通用户判断禁言*/
enum chat_msg_type{WHISPER_JUDGE = 9, WHISPER, EXIT_WHISPER, GROUP, SILENCE_JUDGE};
/*管理员特殊权限              踢人             禁言     关闭服务器与所有客户端 */
enum administrator_privileges{KICKED_OUT = 14, SILENCE, CLOSE,                 };
/*   作者特殊权限      增加管理员   */
enum author_privileges{ADDING_ADMIN = 17};
/*   管理员申请 判断           管理员身份判断  管理员申请   */
enum administrator_application{ADMIN_JUDGE = 18,    ADMIN_APPLY};

/* 来自终端声明 */
void cancel_judge_mark(char *src);
void cancel_msg_spaces(char *src);
char inquire_msg_type(int sockfd,link_msg p_terminal);
void display_help();
int whisper_judgment(int sockfd,link_msg p_terminal);
int silence_judgment(int sockfd,link_msg p_terminal);
void exit_whisper(link_msg p_terminal);
void change_login_status(int sockfd,link_msg p_terminal);
void kicked_out_user(int sockfd, link_msg p_terminal);
void silence_user(int sockfd,link_msg p_terminal);
int administrator_judgment(int sockfd,link_msg p_terminal);
void administrator_application(int sockfd,link_msg p_terminal);
void author_adding_administrator(int sockfd,link_msg p_terminal);
int processing_terminal_message(int sockfd,link_msg p_terminal,int fd);
