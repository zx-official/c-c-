#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
int data;
struct node *next;
}node;
node *head =NULL;
//1.创建节点
node *create_node(int data)
{
    node *p =(node*)malloc(sizeof(node));
    if(p == NULL)
    {
        printf("create node filed!");
        exit(1);
    }else
    {
        p ->data = data;
        p ->next = NULL; 
        return p;
    }
}
//2.释放节点
void free_node(node *p)
{
    free(p);
}
//3.插入节点（头插法）
node *insert_node(node* p)
{
    p ->next = head;
    head = p;
}
//删除节点
void del_node(node *p)
{
    node * pre;
    if(head == p)
    {
        head = head->next;
        p->next = NULL;
        free_node(p);
        return ;
    }
    pre = head;
    while(pre->next != NULL)
    {
        if(pre->next == p)
        {
            pre->next = p->next;
            p->next =NULL;
            free_node(p);
        } 
        pre = pre->next;
    }
       

}
//遍历数组
void traverse()
{   node *p=head;
    if(p == NULL)
    {
        printf("列表为空！");
    }
    while(p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
//搜索节点
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
//销毁链表
void destory()
{
    node *p;
    while(head != NULL)
    {
        p =head;
        head = head->next;
        free_node(p);
    }
}
int main(int argc, char const *argv[])
{
    int target;
    for (int i = 0; i < 10; i++)
    {
        node *new_node=create_node(rand()%100+3);
        insert_node(new_node);
    }
    traverse();
    scanf("%d",&target);
    node *find = search_node(target);
    if(find == NULL)
    {
        printf("没找到！");
    }else
    {
        printf("%p %d %d",find,find->data,target);
    }
    printf("\n");
    del_node(find);
    traverse();
    printf("\n");
    destory();
    traverse();
    
    return 0;
}
