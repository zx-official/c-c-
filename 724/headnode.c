#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node
{
    int data;
    struct node *next;
}node;
node head_node ={0,NULL};
node *head = &head_node;
node *create_node(int data)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
//插入时排序
void inserting_sort_node(node *p)
{
    node *pre = head;
    while (pre->next != NULL)
    {
        if(p->data < pre->next->data)
        {
            break;
        }
        pre = pre->next;
    }
    p->next = pre->next;
    pre->next = p;
}
void traverse()
{
    node *p =head->next;
    while (p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }   
    printf("\n");
}
//头插法
void head_insert(node *p)
{
    
    p->next = head->next;
    head->next = p;
}
void reverse()
{
    node *temp;
    node *p = head->next;
    head->next=NULL;
    while (p != NULL)
    {
        temp = p;
        p = p->next;
        head_insert(temp);
    }
    
}
void free_node(node *p)
{
    free(p);
}
node *search_node(int target)
{
    node *p = head->next;
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
void del_node(node *target)
{
    node *pre = head->next;
    while (pre->next != NULL)
    {
        if(pre->next == target)
        {
            pre->next =target->next;
            target->next = NULL;
            free_node(target); 
        }
        pre = pre->next;
    }
  
}
void destroy_link()
{
    node *p = head->next;
    while (p != NULL)
    {
        node *temp =p;
        p = p->next;
        temp->next = NULL;
        free_node(temp);
    }
    head->next = NULL;
    free_node(head);
} 
//对构建好的无序链表插入排序
void insert_sort()
{
    node *temp;
    node* p = head->next;
    head->next = NULL;
    while (p !=NULL)
    {
        temp = p;
        p = p->next;
        inserting_sort_node(temp);
    }
    
}
void tail_insert(node *p)
{
    if (head ->next == NULL)
    {
        head->next = p;
        return ;
    }
    node *q = head->next;
    while (q->next != NULL)
    {
        q = q->next;
    }
    q->next = p;
    p->next = NULL;
}
//p指向又数据域的第一个节点，使用前把头节点后面断开
void recession_reverse(node *p) {
    if(p->next != NULL)
    {
        node *temp=p;
        p = p->next;
        temp->next=NULL;
        head_insert(temp);
    }
    
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        node *new_node = create_node(rand()%100+1);
        inserting_sort_node(new_node);
    }
    traverse();
    //node *p = head->next;
    //head->next = NULL;
    //recession_reverse(p);
    traverse();
   // insert_sort();
    //traverse();
    
    return 0;
}


