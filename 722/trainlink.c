#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node;

node *head =NULL;
node *create_node(int data)
{
    node *new_node = (node *)malloc(sizeof(node));
    if(new_node == NULL)
    {
        printf("create filed!\n");
    }else
    {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}
void insert_node(node *p)
{
    p->next = head;
    head = p;
}
void traverse()
{
    if(head ==NULL)
    {
        printf("链表为空！");
        return;
    }
    node *p = head;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
node *search_node(int target)
{
    node *p = head;
    while(p !=NULL)
    {
        if(p->data == target)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
void free_node(node *p)
{
    free(p);
}
void del_node(node *target)
{
    node *pre = head;
    while (pre != NULL)
    {
        if(pre->next == target)
        {
            pre->next = target->next;
            target->next = NULL;
            free_node(target);
            return ;
        }
        pre = pre->next;
    }
        printf("没找到该节点，无法删除！\n");
}
void destory_link()
{
    while(head != NULL)
    {
        node *p =head;
        head = head->next;
        p->next = NULL;
        free_node(p);
    }
    free_node(head);
}
int main(int argc, char const *argv[])
{
    int index;
    for(int i = 0; i < 10;i++)
    {
        node *new_node=create_node(10*i+i);
        insert_node(new_node);
    }
    traverse();
    scanf("%d",&index);
    node *find = search_node(index);
    if(find != NULL)
    {
        printf(" %p %d %d",find,find->data,index);
    }else
    {
        printf("find filed!");
    }
    del_node(find);
    traverse();
    destory_link();
    traverse();
    return 0;
}

