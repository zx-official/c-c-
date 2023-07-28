#include<stdio.h>
#include<string.h>
void point_insert_sort(int *v,int len)
{
    int *current = v+1;
    for (current; current < v+len; current++)
    {
        int value = *current;
        //j指针代表有序区
        int *j =current - 1;
        for (j; j > v && value < *(j); j--)
        {
            *(j+1) = *j;
        }
        *(j+1) = value;
    }
    

}
void insert_sort(int *v,int len)
{
    int j;
    for(int i = 1; i < len ;i++)
    {
        int value = v[i];
        for( j = i; j-1 > 0 && value< v[j-1];j--)
        {
            v[j] = v [j-1];
        }
        v[j] = value;
        
    }
}
void print_array(int *v,int len)
{
    for(int i = 0; i <len; i++)
    {
        printf("%d ",v[i]);
    }
        printf("\n");
}
int main()
{
    int test[]={1,6,2,8,5};
    int len =sizeof(test)/sizeof(test[0]);
    print_array(test,len);
    point_insert_sort(test,len);

    print_array(test,len);
    return 0;

}
