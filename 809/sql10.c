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
 *10.【2010统考真题】设将n(n>1）个整数存效到一维数组R中。
    设计一个在时间和空间两方面都尽可能高效的算法。将R中保存的序列循环左移p(O<p<n）个位置，
    即将R中的数据由(X_0,X_1,…,X_(n-1))变换为(X_p,X_(p+1),…,X_(n-1),X_0,X_1,…,X_(p-1))。
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
void shift_left(sq_list *list,int num)
{
    traverse_all(list->array,0,list->len-1);
    traverse_all(list->array,0,list->len-1-num);
    traverse_all(list->array,list->len-num,list->len-1);
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
    shift_left(&list,3);
    print_array(&list);
    return 0;
}
