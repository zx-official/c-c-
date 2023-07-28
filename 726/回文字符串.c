#include<stdio.h>
#include<string.h>
int is_palindrom(char *str)
{
    char *begin = str;
    char *end = str + strlen(str) - 1;
    while (begin < end)
    {
        if(*begin != *end)
        {
            return 0;
        }
        begin++;
        end--;
    }
    return  1;
}
int main(int argc, char const *argv[])
{
    char *s1 = "12321";
    printf("%d\n",is_palindrom(s1));
    return 0;
}
