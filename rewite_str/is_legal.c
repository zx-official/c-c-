#include "functional.h"
#include<stdio.h>
char *is_leagl(char *src,char *start,char *end)
{   
     char *first = my_strstr(src, start);
    if (first == NULL) 
    {
        return NULL;
    }

    char *last = my_strstr(first, end);
    if (last == NULL) 
    {
        return NULL;
    }

    *last = '\0';
    return first + my_strlen(start);

}