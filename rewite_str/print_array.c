#include<stdio.h>
void my_print_array(char *src)
{
    while (*src != '\0')
    {
        printf("%c",*src);
        src++;
    }
    
}