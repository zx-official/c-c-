#include "functional.h"
#include <stdio.h>
char *my_strstr(char *str1,char *str2)
{   
    int len  = my_strlen(str2);
    while (*str1 != '\0')
    {
        if(my_strncmp(str1,str2,len) == 0)
        {
            return str1;
        }
        str1++;
    }
    return NULL;
}