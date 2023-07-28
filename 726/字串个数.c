#include<stdio.h>
#include<string.h>
int str_times(char *str,char *sub)
{
    int len = strlen(sub);
    int total = 0;
    while (*str != '0')
    {
        if(strncmp(str,sub,len) == 0)
        {
            total++;
        }
    }
    
}