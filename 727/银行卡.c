#include<stdio.h>
#include<string.h>
void is_legal(char *src)
{
    int len = strlen(src);
    char *end = src + len -1;
    int bit = 1;
    int odd_total = 0;
    int even_total = 0;
    while (end != src-1)
    {
        if(bit % 2 == 0)
        {
            if((*end - '0') *2 >= 10)
            {
                even_total = even_total + (*end - '0') *2-9;
            }else
            {
                 even_total = even_total + (*end - '0') *2;
            }            
        }else
        {
            odd_total = odd_total + (*end - '0');
        }
        bit++;
        end--;
    }
    if((odd_total + even_total)%10 == 0)
    {
        printf("成功！\n");
    }else
    {
         printf("不成功！\n");
    }
}
int main(int argc, char const *argv[])
{
    char test[]= "356827027232780";
    is_legal(test);
    return 0;
}
