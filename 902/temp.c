#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book
{
    int id;
    char name[20];
    char publich[20];
    int money;
    struct book* next;
}book;

book *head = NULL;

book *mk_book(int id, char *name, char *publich, int money)
{
    book *p = (book *)malloc(sizeof(book));

    if (p == NULL)
    {
        printf("malloc filed\n");
        exit(1);
    }

    p->id = id;
    strcpy(p->name, name);
    strcpy(p->publich, publich);
    p->money = money;
    p->next = NULL;

    return p;
}

void insert_book(book *p)
{
    p-> next = head;
    head = p;
}

void traverse()
{
    book *p = head;

    while (p != NULL)
    {
        printf("%d %s %s %d\n", p->id, p->name, p->publich, p->money);
        p = p->next;
    }
    printf("\n");
}

void insert_l2b(book *p)
{
	book *pre = head;

    if(pre == NULL || p->money < pre->money)
    {
        p->next = head;
        head = p;
        return;
    }

    while(pre->next != NULL)
    {
        if(p->money < pre->next->money)
        {
            break;
        }
        pre = pre->next;
    }
    p->next = pre->next;
    pre->next = p;
}
/*void sort(book *p)
{
	book *pre = head;

    if(pre == NULL || p->money < pre->money)
    {
        p->next = head;
        head = p;
        return;
    }

    while(pre->next != NULL)
    {
        if(p->money < pre->next->money)
        {
            break;
        }
        pre = pre->next;
    }
    p->next = pre->next;
    pre->next = p;
}*/

int main()
{
    int id;
    char name[20];
    char publich[20];
    int money;
    book *p;
    int i;
    int n;
    printf("要入库几本书？ ");
    scanf("%d", &n);
    printf("是否要对图书单价进行排序1否2排 ");
    int x;
    scanf("%d", &x);

    for (i = 0; i < n; i++)
    {
        printf("请输入图书编号 ");
        scanf("%d", &id);
        printf("请输入图书名字 ");
        scanf("%s", name);
        printf("请输入图书出版社 ");
        scanf("%s", publich);
        printf("请输入图书价钱 ");
        scanf("%d", &money);
        p = mk_book(id, name, publich, money);
        if (x == 1)
        {
            insert_book(p);
        }
        if (x == 2)
        {
            insert_l2b(p);
        }
    }

    traverse();

    return 0;
}
