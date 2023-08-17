#include <stdio.h>
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
int partition(int a[],int start,int end)
{
    int index  = a[start];
    int i = start+1;
    for (int j = start+1; j <= end; j++)
    {
        if (a[j] < index )
        {
            swap(&a[i],&a[j]);
            i++;
        }

    }
        swap(&a[start],&a[i-1]);
        return (i-1);
    

}
void QuickSort(int a[],int start,int end)
{
    if (start < end)
    {
        int part = partition(a,start,end);
        QuickSort(a,start,part-1);
        QuickSort(a,part+1,end);
    }
    
}
int main(int argc, char const *argv[])
{
    int test[] = {3,6,9,1,5,11,2,1};
    int len = sizeof(test)/sizeof(test[0]);
    QuickSort(test,0,len-1);
    for (int i = 0; i < len; i++)
    {
        printf("%d ",test[i]);
    }
    
    return 0;
}