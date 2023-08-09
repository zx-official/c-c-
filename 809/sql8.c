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
 *8.已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,a3…,am)和(b1,b2, b3…, bn).
 *  试编写一个函数，将数组中两个顺序表的位置互换，即将(b1, b2, b3…, bn). 放在(a1, a2, a3…, am)的前面。
 即 a1,a2,a3…,am,b1,b2, b3…, bn 转换成 b1,b2, b3…, bn,a1,a2,a3…,am
 */
void traverse_all(int *a,int begin,int end)
{
    int temp;
    while (begin < end)
    {
        temp = a[begin];
        a[begin] = a[end];
        a[end] = temp;
        begin++;
        end--;
    }
    
}
void part_traevrse(sq_list *list,int m,int n)
{
    traverse_all(list->array,0,n+m);
    traverse_all(list->array,0,n);
    traverse_all(list->array,n+1,n+m);
}
int main(int argc, char const *argv[])
{
    sq_list list ;
    init_list(&list);
    for (int i = 1; i < 10; i++)
    {
        insert_elm(i,&list);
    }
    print_array(&list);
    part_traevrse(&list,5,3);
    print_array(&list);
    return 0;
}
