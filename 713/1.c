#include <stdio.h>

char *rm_blank(char *dest, char *src)
{
    char *o_dest = dest;
    while (*src != '\0')
    {
        if (*src == ' ')
        {
            src++;
            continue;
        }
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return o_dest;
}

char *my_strcpy(char *dest, char *src)
{
    char *o_dest = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';

    return o_dest;
}


int my_strlen(char *str)
{
    int len = 0;

    while (*str != '\0')
    {
        len++;
        str++;
    }

    return len;
}

void strupper(char *str)
{
    while (*str != '\0')
    {
        if (*str >= 'a'&& *str <= 'z')
        {
            *str = *str + ('A' - 'a');
        }
        str++;
    }
}

int main(int argc, char const *argv[])
{
    char str[20];
    char *src = "   I love China!   ";

    printf("|||%s|||\n", rm_blank(str, src));

    return 0;
}