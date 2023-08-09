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
void   insert_elm(int num,sq_list *list)
{
    int len = list->len;
    list->array[len] = num;
    list->len++;
}
/* 顺序表练习题*/


/*1.从顺序表中删除具有最小值的元素(假设唯一)并由函数返回被删元素的值，
    空出的位置由最后一个元素填补，若顺序表为空则显示出错信息并退出运行.
*/
void init_list(sq_list *list)
{

    list->len = 0;
}
int  delete_elem(sq_list * list)
{
    int min = list->array[0];
    int index;
    for (int i = 0; i < list->len; i++)
    {
        if (list->array[i] < min)
        {
            min = list->array[i];
            index = i;
        }
    }
    list->array[index] = list->array[(list->len)-1];
    return min;
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
    int del =delete_elem(&list);
    printf("delete elem is %d\n",del);
    print_array(&list);
    return 0;
}
