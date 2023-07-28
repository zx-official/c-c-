#include "functional.h"
int my_strlcpy(char *dest,char *src,int n)
{
    int i;
    for( i = 0; i< n-1 && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return my_strlen(dest);
}