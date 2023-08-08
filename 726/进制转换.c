#include<stdio.h>
char *itoa(unsigned int x,int scale,char *buf)
{   
    int low;
    int i = 0;
    while (x > 0)
    {
        low = x % scale;
        if(low > 10)
        {
            low = low -10 + 'A';
        }else
        {
            low = low + '0';
        }
        buf[i] =  low;
        x /= scale;
        i++;
    }
    buf[i] = '\0';
    str_rev(buf);
    return buf;
}
int main(int argc, char const *argv[])
{
    char buf[20];
    itoa(12345,2,buf);
    printf("%s\n",buf);
    return 0;
}
