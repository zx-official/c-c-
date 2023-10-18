/*************************************************************************************
文件名：administrator.h
文件功能：服务器管理人员操作表 
          可以通过宏的数值来控制服务器的监测能力范围，
          管理员关闭服务器的倒计时秒数
*************************************************************************************/

#ifndef _ADMINISTRATOR_H_
#define _ADMINISTRATOR_H_

static char *password = "19920623";                         //申请管理员所需要的密码
#define LOGIN_WAIT_TIME                              1      //被管理员踢出的用户再登录的等待分钟数
#define MSG_LEN                                      1000    //消息的长度

/****************************************显示所有监测信息***************************************/
#if 1
#define MONITORING_CLIENT_OPEN                       1      //服务器监测客户端开启
#define MONITORING_CLIENT_CLOSE                      1      //服务器监测客户端关闭
#define MONITORING_CLIENT_HEALTH_TIPS                5      //服务器监测客户端温馨提示开启秒数
#define CLOSE_COUNTDOWN                              10     //服务器监测管理员关闭服务器的倒计时秒数
#define MONITORING_DISPLAY_USER_LIST                 1      //服务器显示用户帐号密码信息
#define MONITORING_USER_REGISTER_REQUEST             1      //服务器监测用户注册请求
#define MONITORING_USER_LOGIN_REQUEST                1      //服务器监测用户登录请求
#define MONITORING_USER_LOGIN_STATUS                 1      //服务器监测用户登录状态
#define MONITORING_USER_DOWNLINE                     1      //服务器监测用户下线
#define MONITORING_USER_WHISPER_REQUEST              1      //服务器监测用户私聊请求
#define MINOTORING_USER_DISCONNET_WHISPER            1      //服务器监测用户断开私聊关系
#define MONITORING_USER_CHAT_REQUEST                 1      //服务器监测用户聊天请求
#define MONITORING_USER_WHISPER_CONTENTS             1      //服务器监测用户私聊内容
#define MONITORING_USER_GROUP_CHAT_CONTENTS          1      //服务器监测用户群聊内容
#define MONITORING_USER_HELP_QUERY                   1      //服务器监测用户查看帮助界面
#define MONITORING_USER_ONLINE_ID_QUERY              1      //服务器监测用户在线ID查询
#define MONITORING_USER_APPLICATION_ADMINISTRATOR    1      //服务器监测普通用户申请管理员权限
#define MONITORING_ADMINISTRATOR_KICKED_OUT_USER     1      //服务器监测管理员踢人
#define MONITORING_ADMINISTRATOR_CLOSE_SERVER_CLIENT 1      //服务器监测管理员关闭服务器以及所有客户端
#define MONITORING_ADMINISTRATOR_SILENCE_USER        1      //服务器监测管理员禁言用户
#endif

/****************************************关闭所有监测信息***************************************/
#if 0
#define MONITORING_CLIENT_OPEN                       0      //服务器监测客户端开启
#define MONITORING_CLIENT_CLOSE                      0      //服务器监测客户端关闭
#define MONITORING_CLIENT_HEALTH_TIPS                0      //服务器监测客户端温馨提示开启秒数
#define CLOSE_COUNTDOWN                              0      //服务器监测管理员关闭服务器的倒计时秒数
#define MONITORING_DISPLAY_USER_LIST                 0      //服务器显示用户帐号密码信息
#define MONITORING_USER_REGISTER_REQUEST             0      //服务器监测用户注册请求
#define MONITORING_USER_LOGIN_REQUEST                0      //服务器监测用户登录请求
#define MONITORING_USER_LOGIN_STATUS                 0      //服务器监测用户登录状态
#define MONITORING_USER_DOWNLINE                     0      //服务器监测用户下线
#define MONITORING_USER_WHISPER_REQUEST              0      //服务器监测用户私聊请求
#define MINOTORING_USER_DISCONNET_WHISPER            0      //服务器监测用户断开私聊关系
#define MONITORING_USER_CHAT_REQUEST                 0      //服务器监测用户聊天请求
#define MONITORING_USER_WHISPER_CONTENTS             0      //服务器监测用户私聊内容
#define MONITORING_USER_GROUP_CHAT_CONTENTS          0      //服务器监测用户群聊内容
#define MONITORING_USER_HELP_QUERY                   0      //服务器监测用户查看帮助界面
#define MONITORING_USER_ONLINE_ID_QUERY              0      //服务器监测用户在线ID查询
#define MONITORING_USER_APPLICATION_ADMINISTRATOR    0      //服务器监测普通用户申请管理员权限
#define MONITORING_ADMINISTRATOR_KICKED_OUT_USER     0      //服务器监测管理员踢人
#define MONITORING_ADMINISTRATOR_CLOSE_SERVER_CLIENT 0      //服务器监测管理员关闭服务器以及所有客户端
#define MONITORING_ADMINISTRATOR_SILENCE_USER        0      //服务器监测管理员禁言用户
#endif

#endif
