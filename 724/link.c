#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}node;
node *k = {0,NULL};
node *head = &k;
node *create_node(int data)
{
    node * new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
}
void insert_node(node *p)
{
    p->next = head->next;
    head = p;
}
void traverse()
{
    if(head == NULL)
    {
        printf("链表为空\n");
    }
    node *p = head->next;
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
node *search_node(int target)
{
    node *p =head;
    while (p != NULL)
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
void del_node(node *p)
{
    if(head == p)
    {
        head = head->next;
        p->next = NULL;
        free_node(p);
    }
    
    node *pre = head;
    while (pre->next != NULL)
    {
        if(pre->next == p)
        {
            pre->next = p->next;
            p->next = NULL;
            free_node(p);
        }
        pre = pre->next;
    }
    
}
void destroy_link()
{
    while (head != NULL)
    {
        node *p =head;
        head = head->next;
        p->next = NULL;
        free_node(p);
    }
}
//链表的插入排序
void insert_sort_link()
{
    node *p = head;

}
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 6; i++)
    {
        node *new_node = create_node(i*5);
        insert_node(new_node);
    }
    traverse();
    int target;
    scanf("%d",&target);
    node *find = search_node(target);
    if(find == NULL)
    {
        printf("没找到\n");
    }else
    {
        printf("%p %d %d \n",find,find->data,target);
    }
    del_node(find);
    traverse();
    destroy_link();
    traverse();
    return 0;
}
