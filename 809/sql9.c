#include <stdio.h>
#define MAXSIZE 100
typedef struct 
{
    int array[MAXSIZE];
    int len;
}sq_list;

void print_array(const sq_list *s)
{
	int i;
	for (i = 0; i < s->len; i++)
	{
		printf("%3d ", s->array[i]);
	}
	printf("\n");
}
void init_list(sq_list *list)
{

    list->len = 0;
}
void   insert_elm(int num,sq_list *list)
{
    int len = list->len;
    list->array[len] = num;
    list->len++;
}
/*
 *9.线性表(a1, a2, a3…, an)中的元素递增有序且按顺序存储于计算机内。
	要求设计一算法，完成用最少时间在表中查找数值为x的元素，若找到则将其与后继元素位置相交换，
	若找不到则将其插入表中并使表中元素仍递增有序。
 */
void insert_sort(sq_list *list,int len,int target)
{
    int j;
    for (int i = 0; i < len; i++)
    {
        if(target < list->array[i])
        {
            for ( j = len-1;list->array[j] > target; j--)
            {
                list->array[j+1] = list->array[j];
            }
            list->array[j+1] = target;
            list->len++;
            break;
        }
    }
    
}
int find (sq_list *list,int target,int begin, int end)
{
    //     int begin = 0;
    // int end = list->len -1;
     int mid;
    while (begin <= end)
    {
        mid = (begin +end)/2;
        if(list->array[mid] == target)
        {
            return mid;
        }
        else if (list->array[mid] > target)
        {
           end = mid -1;
        }
        else if (list->array[mid] <target)
        {
            begin = mid + 1;
        }      
    }
    return -1;
}
void funciotnal(sq_list *list,int target)
{
    int begin = 0;
    int end = list->len-1;
    int index = find(list,target,begin,end);
    if(index == -1)
    {
        insert_sort(list,list->len,target);
    }else
    {
        int temp = list->array[index];
        list->array[index] = list->array[index+1];
        list->array[index+1] = temp;

    }
    
    
}
int main(int argc, char const *argv[])
{
    sq_list list ;
    init_list(&list);
    for (int i = 1; i < 10; i++)
    {
        insert_elm(i*2,&list);
    }
    print_array(&list);
    funciotnal(&list,7);
    print_array(&list);
    return 0;
}
