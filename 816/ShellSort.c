#include <stdio.h>
void insertSort(int a[],int len)
{
    for (int i = 1; i < len; i++)
    {
        int current = a[i];
        int j;
        for ( j = i -1; j >=0 && a[j] > current ; j--)
        {
            a[j+1] = a[j];
        }
        a[j+1] = current;
    }
    
}
void ShellSort(int a[],int len)
{
    int j;
    for (int gap = len/2; gap > 0; gap /=2)
    {
        for (int i = 1; i < len; i++)
    {
        int current = a[i];
        for ( j = i; j >= gap && a[j-gap] > current ; j-=gap)
        {
            a[j] = a[j-gap];
        }
        a[j] = current;
    }
    }
    
        
    
    
}
int main(int argc, char const *argv[])
{
    int test[] = {2,5,7,1,6,9,11,10};
    int len = sizeof(test)/sizeof(test[0]);
    ShellSort(test,len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ",test[i]);
    }
    
    return 0;
}

