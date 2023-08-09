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
}
/*
 *4.从有序顺序表中删除其值在给定值s与t之间(要求s < t)的所有元素，
 *  如果s或t不合理或顺序表为空，则显示出错信息并退出运行。
 */
void del_regular(sq_list *list, int s, int t)
{
    int len = list->len;
    int begin = -1; // 初始化为无效值
    int end = -1;   // 初始化为无效值

    // 找到符合条件的 begin 和 end
    for (int i = 0; i < len; i++)
    {
        if (list->array[i] <= s)
        {
            begin = i;
        }
        if (list->array[i] >= t)
        {
            end = i;
            break;
        }
    }

    if (begin == -1 || end == -1)
    {
        printf("Invalid range or empty list.\n");
        return; // 退出函数
    }

    int left = len - end - 1;
    for (int i = 0; i < left; i++)
    {
        list->array[begin + i] = list->array[end + i + 1];
    }

    list->len = len - (end - begin + 1);
}

int main(int argc, char const *argv[])
{
    sq_list list;
    init_list(&list);
    insert_elm(2,&list);
    insert_elm(3,&list);
    insert_elm(4,&list);
    insert_elm(5,&list);
    insert_elm(6,&list);
    insert_elm(9,&list);
    print_array(&list);
    del_regular(&list,3,5);
    print_array(&list);
    return 0;
}

