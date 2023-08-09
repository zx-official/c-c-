#include <stdio.h>
#include <stdlib.h>
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
}/*
 *5.从顺序表中删除其值在给定值s与t之间(包含s和t，要求s < t）的所有元素，
    如果s或t不合理或顺序表为空，则显示出错信息并退出运行。
 */
void del(sq_list *list,int s,int t)
{
    int len = list->len;
    int j = 0;
    if(len ==0)
    {
        printf("zero\n");
        exit(-1);
    }
    if(t < s)
    {
        printf("illegal input\n");
        exit(-1);
    }
    for (int i = 0; i < len; i++)
    {
        if(list->array[i] < s || list->array[i] > t)
        {
            list->array[j] = list->array[i];
            j++;
        }else 
        {
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
    insert_elm(4,&list);
    insert_elm(1,&list);
    insert_elm(9,&list);
    print_array(&list);
    del(&list,2,4);
    print_array(&list);
    return 0;
}