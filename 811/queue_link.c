#include <stdio.h>
#include <stdlib.h>
#define ERR -8080
//先了解一个事实，在实际调用时，只可能是传入的是两个指向队列的指针,
//不可能传入整个队列，所以后续参数列表都是以队头队尾指针
//还有整体方向是从front 指向rear
//还有，这个版本的front指向的是 哑节点
typedef struct queue_node
{
    int data;
    struct queue_node *next;
}queue_node,*queue_ptr;
typedef struct 
{
    queue_ptr front,rear;
}link_queue;

void init_queue(link_queue *Q)
{
    Q->front = Q->rear =(queue_ptr)malloc(sizeof(queue_node));
    if(!Q->front)
    {
        printf("分配内存失败！\n");
        exit(-1);
    }
    Q->front->next = NULL;
}
void enqueue(link_queue *Q,int data)
{
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    if(!new_node)
    {
        printf("malloc failed \n");
        exit (-1);
    }
    new_node->data =data;
    Q->rear->next = new_node;
    Q->rear = new_node;
}
void dequeue(link_queue *Q, int *de_elem)
{
    if (Q->rear == Q->front)
    {
        printf("queue is empty ! \n");
        exit(-1);
    }
    
    queue_ptr temp = Q->front->next;
    Q->front->next = temp->next;
    *de_elem = temp->data;
    temp->next = NULL;
    free(temp);
}
void destory_queue(link_queue *Q)
{
    while (Q->front != Q->rear)
    {
        queue_ptr temp = Q->front;
        Q->front = Q->front->next;
        temp->next =NULL;
        free(temp);
    }
    Q->rear = Q->front = NULL;
}
void clear_queue(link_queue *Q)
{
    while (Q->front != Q->rear)
    {
        queue_ptr temp = Q->front;
        Q->front = Q->front->next;
        temp->next =NULL;
        free(temp);
    }
}
//由于带*会导致真实操作指针的位置
//所以在不需要时传入副本计算更安全

int is_empty(link_queue Q)
{
    return Q.front == Q.rear;
}
int queue_lenth(link_queue Q)
{
    int total = 0;
    while (Q.front != Q.rear)
    {
        total++;
        Q.front = Q.front->next;
    }
    
    return total;
}
//展示使用传出参数版本获取元素
void get_front(link_queue Q,int *target)
{
    if (Q.front == Q.rear)
    {
        *target = ERR;
    }else
    {
        *target = Q.front->next->data;
    }    
}
void traverse_queue(link_queue Q)
{
    queue_ptr p  = Q.front->next;
    while (p != NULL)
    {
        printf("%d\n",p->data);
        p = p->next;
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    link_queue Queue;
    init_queue(&Queue);
    for (int i = 0; i < 6; i++)
    {
        enqueue(&Queue,i*3);
    }
    traverse_queue(Queue);
    int del_elem;
    int cur_elem;
    dequeue(&Queue,&del_elem);
    printf("delete elem is %d\n",del_elem);
    traverse_queue(Queue);
    get_front(Queue,&cur_elem);
    printf("current top elem is %d\n",cur_elem);
    traverse_queue(Queue);
    return 0;
}
