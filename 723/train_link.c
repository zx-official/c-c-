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
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
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
        printf("链表为空\n");
    }
    node *p = head;
    while (p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
node *search_node(int target)
{
    node *p = head;
    while(p != NULL)
    {
        if(p->data == target)
        {
            //printf("%p %d %d",p,p->data,target);
            return p;
        }
        p = p ->next;
    }
    return NULL;
}
void free_node(node *p)
{
    free(p);
}
void del_node(node *p)
{
    node *pre =head;
    if(head == p)
    {
        head = head->next;
        p->next = NULL;
        free_node(p);
    }else
    {
        while (pre->next != NULL)
        {
            if(pre->next == p)
            {
                pre->next = p->next;
                p->next = NULL;
                free_node(p);
                return ;
            }
            pre = pre->next;
        }
        
    }
}
void destory_link()
{
    while(head != NULL)
    {
        node *p = head;
        head = head->next;
        p->next = NULL;
        free_node(p);
    }
}
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 7; i++)
    {
        node *new_node = create_node(rand()%101+i);
        insert_node(new_node);
    }
    traverse();
    int want;
    scanf("%d",&want);
    node *find = search_node(want);
    if (find != NULL)
    {
        printf("%p %d %d\n",find,find->data,want);
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
