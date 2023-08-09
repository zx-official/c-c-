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
 *7.将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表。
 */
sq_list gather(sq_list *list1,sq_list *list2)
{
    sq_list g_list;
    g_list.len = 0;
    int index1 = 0;
    int index2 = 0;
    while (index1 < list1->len  && index2 <list2->len)
    {
            if (list1->array[index1] < list2->array[index2])
        {
            g_list.array[g_list.len++] = list1->array[index1++];
        }else 
        {
            g_list.array[g_list.len++] = list2->array[index2++];
        }
    }
    while(index1 < list1->len)
    {
        g_list.array[g_list.len++] = list1->array[index1++];
    }

      while(index2 < list1->len)
    {
        g_list.array[g_list.len++] = list2->array[index2++];
    }
    
    return g_list;

}
int main(int argc, char const *argv[])
{
    sq_list list1;
    sq_list list2;
    sq_list g_list;
    init_list(&list1);
    init_list(&list2);
    for (int i = 3 ;i < 7; i++)
    {
        insert_elm(i,&list1);
        insert_elm((i-2)*2,&list2);
    }
    print_array(&list1);
    print_array(&list2);
    g_list = gather(&list1,&list2);
    print_array(&g_list);
    return 0;
}
