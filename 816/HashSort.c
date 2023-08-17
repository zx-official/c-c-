#include <stdio.h>
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void max_heap(int a[],int len,int i)
{
    int largest = i;
    int left = i*2+1;
    int right = i*2+2;

    if (left < len && a[left] > a[largest])
    {
        largest = left;
    }
    if (right < len && a[right] > a[largest])
    {
        largest = right;
    }
    if (largest != i  && a[largest] != a[i])
    {
        swap(&a[i],&a[largest]);
        max_heap(a,len,largest);
    }
}
void HeapSort(int a[],int len)
{
    for (int i = len/2 -1; i >= 0; i--)
    {
        max_heap(a,len,i);
    }
    for (int i = len -1; i >=0 ; i--)
    {
        swap(&a[0],&a[i]);
        max_heap(a,i,0);
    }
    
}
int main(int argc, char const *argv[])
{
    int test[] = {3,6,9,1,5,11,2,1};
    int len = sizeof(test)/sizeof(test[0]);
    HeapSort(test,len);
    for (int i = 0; i < len; i++)
    {
        printf("%d ",test[i]);
    }
    
    return 0;
}
