#include "functional.h"
char *itoa(unsigned int x,int scale,char *buf)
{
    int i;
    int low;
    while (x > 0)
    {
        low =x % scale;
        if(low >= 10)
        {
            low = low -10 +'A';
        }else
        {
            low = low + '0';
        }
        buf[i] = low;
        x = x/scale;
        i++;
    }
    buf[i]= '\0';
    reverse_char(buf,my_strlen(buf));
    return buf;
}