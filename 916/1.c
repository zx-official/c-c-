#include <stdio.h>
int add(int a,int b)
{
    int total = a+b;
    return total;
}
int main()
{   
    int total = 0;
    int i = 0;
    for(i = 0;i <=100;i++)
    {
       total =  add(total,i);
    }
    printf("%d\n",total);
    return 0;

}
