#include "functional.h"
char *my_strncat(char *dest,char *src,int n)
{
    int len = my_strlen(dest);
    int i;
    for ( i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[len+i] = src[i];
    }
    dest[len +i] = '\0';
    return dest;
}