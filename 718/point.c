#include<stdio.h>
#include <string.h>
int del_substr(char *str,char const *substr)
{//BF算法实现字符串匹配
    //创建两个备份指针
    char *chp =str;
    char *subp =substr;
    int o_len =strlen(str);
    int t_len =strlen(substr);
    while(*chp != '\0')
    {
        if(*chp == *subp)
        {   
            chp++;
            subp++;
        }else
        {
            chp = str;
        }
    }
    if(*(str)==*(substr))
    {
        return 1;
    }else
        return 0;   

}
