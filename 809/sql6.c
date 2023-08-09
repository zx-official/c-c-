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
 6.从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。
 */
void del_exist(sq_list *list)
{
    int j = 0;
    int len =list->len;
    for (int i = 1; i < list->len; i++)
    {
        if (list->array[i] == list->array[j])
        {
            len--;
        }else 
        {
            j++;
            list->array[j] = list->array[i];
        }
        
        
    }
    list->len = len;

}
int main(int argc, char const *argv[])
{
    sq_list list;
    init_list(&list);
    insert_elm(2,&list);
    insert_elm(3,&list);
    insert_elm(3,&list);
    insert_elm(4,&list);
    insert_elm(4,&list);
    insert_elm(4,&list);
    insert_elm(4,&list);
    insert_elm(5,&list);
    insert_elm(6,&list);
    print_array(&list);
    del_exist(&list);
    print_array(&list);
    return 0;
}