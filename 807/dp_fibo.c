#include <stdio.h>
int fifo(int n,int *a)
{

    if(n == 1 || n == 2 )
    {
        a[n] = 1;
        return a[n];
    }else
    {
        if (a[n-1] == 0) {
            a[n-1] = fifo(n-1,a);
        }
        if (a[n-2] == 0) {
            a[n-2] = fifo(n-2,a);
        }
        
        a[n] = a[n-1] + a[n-2];
    }
    
    return a[n];

}
int main(int argc, char const *argv[])
{
    int test =5;
    int a[6]={0};
    printf("fifo(%d)的值为：%d",test,fifo(test,a));
    return 0;
}
