#include<stdio.h>
#include<string.h>
void my_memcpy (void *dest, void *src,size_t n)
{
    size_t i;
    char *dest_c = dest;
    char *src_c = src;
    for ( i = 0; i < n; i++)
    {
        dest_c[i] = src_c[i];
    }
    return dest;
}
char *my_strstr()
{
    //strncpy实现
}
int main(int argc, char const *argv[])
{
    char *s1 = "I love china fovever";
    char *s2 = "china";
    char *p = strstr(s1,s2);
    if( p == NULL)
    {
        printf("没找到");

    }else
    {
        printf("%s\n",p);
    }

    return 0;
}

