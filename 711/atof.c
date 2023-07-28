#include<stdio.h>
#include<math.h>
double my_atof(char *str)
{
    double total;
    int flag = 1;
    int point =0;
    while(*str == ' ')
    {
        str++;
    }
    if(*str == '-')
    {
    flag = -1;
    str++;
    }
    else if(*str == '+')
    {
    str++;
    }

    while((*str >= '0' &&*str <= '9')||*str == '.')
    {
    total = total * 10 + *str;
        str++;
        if(*str == '.')
        {
             str++;
             point--; 
        }
    }
    return total*pow(10,point);
}
int main()
{
    double total = 0;
    char *p="    123.456abc";
    total = my_atof(p);
    printf("%lf",total);
}
