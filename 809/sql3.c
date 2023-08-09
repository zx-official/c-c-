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
 *3.对长度为n的顺序表L，编写一个时间复杂度为O(n)、空间复杂度为O(1)的算法，
    该算法删除线性表中所有值为x的数据元素，
 */
void delte_all_same_elm(sq_list *list,int target)
{
    int len = list->len;
    int j =0;
    for (int i = 0; i < len; i++)
    {
        if (list->array[i] != target)
        {
            list->array[j] = list->array[i];
            j++;
        }else 
        {
            list->array[j] = list->array[i+1];
            list->len--;
        }  
    }
    
    
    
}
int main(int argc, char const *argv[])
{
    sq_list list;
    init_list(&list);
    insert_elm(2,&list);
    insert_elm(3,&list);
    insert_elm(1,&list);
    insert_elm(4,&list);
    insert_elm(1,&list);
    insert_elm(9,&list);
    print_array(&list);
    delte_all_same_elm(&list,1);
    print_array(&list);
    return 0;
}
