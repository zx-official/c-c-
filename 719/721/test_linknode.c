//链表的基本操作(创建节点、插入节点、遍历链表、查找、删除节点 销毁链表)
#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;   
    struct node* next;
}node;
node *head =NULL;
node *create_node(int data)
{
    node *new_newnode = (node *)malloc(sizeof(node));
    new_newnode->data = data;
    new_newnode->next =NULL;
    return new_newnode;
}
void insert_node(node *p)
{
    p->next= head;
    head = p;
}
void traverse()
{
    if(head ==NULL)
    {
        printf("没有节点!");
    }
    node *p =head;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
void free_node(node *p)
{
    free(p);
}
node *search_node(int target)
{
    node *p =head;
    while(p != NULL)
    {
        if(p->data == target)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
    
}
void del_node(node *p)
    {
        if(p ==NULL)
        {
            printf("参数错误!");
        }
        if(head == p)
        {
            head = head->next;
            free_node(p);
            return;
        }
        node *pre =head;
        while(pre->next != NULL)
        {
            if(pre->next ==p)
            {
                pre->next = p->next;
                free_node(p);
            }
            pre =pre->next;
        }
        
    }
void destory_link()
{
    node *p;
    while (head != NULL)
    {
        p=head;
        head = head->next;
        free_node(p);
    }
    
}
int main(int argc, char const *argv[])
{
    for(int i = 0; i<6; i++)
    {
        node* new_node=create_node(rand()%100+2);
        insert_node(new_node);
    }
    traverse();
    int traget;
    scanf("%d",&traget);
    node *find = search_node(traget);
    if(find ==NULL)
    {
        printf("没找到！\n");
    }else
    {
        printf("%p %d %d \n",find,find->data,traget);
    }
    del_node(find);
    traverse();
    destory_link();
    traverse();
    return 0;
}
