#include "functional.h"
char *my_strcat(char *dest,char *src)
{   
    char *o_dest = dest;
    int len = my_strlen(dest);
    dest = dest +len;
    while (*src != '\0')
    {
        *dest++ =*src++;
    }
        *dest = '\0';
    return o_dest;
}