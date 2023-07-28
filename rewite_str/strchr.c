#include<stdio.h>
char *my_strchr(char *str,char target)
{
    while (*str != '\0')
    {
        if(*str == target)
        {
            return str;
        }
        str++;
    }
    return NULL;
}