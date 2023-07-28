#include<stdio.h>
int my_atoi(char *str)
{
    int total = 0;
    int flag = 1;
    while(*str ==' ')
        {
            str++;
        }
    while(*str !='\0')
    {
        
        if(*str =='-')
        {
            flag = -1;
            str++;
        }
        if(*str == '+')
        {
            str++;
        }
        while(*str >= '0' && *str <= '9')
        {
        total=total * 10+ *str - '0';
        str++;
        }
    }
return total;
}
int main()
{
    char *p ="     -1234abc";
    int total=my_atoi(p);
    printf("%d\n",total);
    return 0;
}
