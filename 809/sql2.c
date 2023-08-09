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
 *2.设计一个高效算法，将顺序表L的所有元素逆置，要求算法的空间复杂度为O(1).
 */
void reversal_sqllist(sq_list *list)
{
    int * begin = list->array;
    int * end = begin +(list->len)-1;
    int len = list->len;
    while (begin < end)
    {
        int temp;
        temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }

}
int main(int argc, char const *argv[])
{
    sq_list list;
    init_list(&list);
    insert_elm(2,&list);
    insert_elm(3,&list);
    insert_elm(4,&list);
    insert_elm(1,&list);
    insert_elm(9,&list);
    print_array(&list);
    reversal_sqllist(&list);
    print_array(&list);
    return 0;
}
