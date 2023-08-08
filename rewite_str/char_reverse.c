#include "functional.h"
void reverse_char(char *src,int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        char temp = src[i];
        src[i] = src[len - 1 - i];
        src[len - 1 - i] = temp;
    }
}
void recursion_reverse_char(char *src,int len)
{
    char *end = src + len - 1;
    if (src < end)
    {
        char temp = *src;
        *src = *end;
        *end = temp;
        recursion_reverse_char(src + 1, len - 2);
    }
}