#include "functional.h"
int word_len(char *src)
{
     int total = 0;
     
    while (*src == ' ')
    {
        src++;
    }

    while (*src != '\0' && *src != ' ')
    {
        src++;
        total++;
    }
    return total;
}
void word_reverse(char *src,int len)
{
    reverse_char(src,len);
    while (*src != '\0')
    {   
        while(*src == ' ')
        {
            src++;
        }
        int lenth =word_len(src);
        reverse_char(src,lenth);
        src +=lenth;
    }
    
}