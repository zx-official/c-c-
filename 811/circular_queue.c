#include <stdio.h>
#include <stdlib.h>
# define MAXSIZE 5
typedef struct queue_node
{
    int data;
    struct queue_node *next; 
}queue_node,*queue_ptr;
typedef struct circular_queue
{
    queue_ptr rear,front;
}circular_queue;
//基础逻辑： 带有哑结点的循环链表front是一直指向哑结点
void init_circular_queue(circular_queue *Q)
{
    Q->front = Q->rear = (queue_ptr)malloc(sizeof(queue_node));

    for (int i = 0; i < MAXSIZE; i++)
    {
        Q->rear->next = (queue_ptr)malloc(sizeof(queue_node));
        Q->rear = Q->rear->next;
    }
    Q->rear->next = Q->front;
    Q->rear = Q->front;
    
} 

void enqueue(circular_queue *Q,int data)
{
    if(Q->rear->next == Q->front)
    {
        printf(" queue max !\n");
        exit(-1);
    }
    queue_ptr new_node =(queue_ptr)malloc(sizeof(queue_node));
    new_node->data = data;
    Q->rear->next = new_node;
    Q->rear = new_node;
}
void traverse_circular_queue(circular_queue Q)
{
    queue_ptr temp = Q.front->next;
    while (temp != Q.rear->next)
    {
        printf("%d\n",temp->data);
        temp = temp->next;
    }
    printf("\n");
}
void dequeue(circular_queue *Q,int *de_elm)
{
    queue_ptr temp;
    queue_ptr real = Q->front->next;
    if(real != Q->rear)
    {
        temp = real;
        Q->front->next = real->next;
        *de_elm = temp->data;
        temp->next = NULL;
        free(temp);
    }else
    {
        printf("queue is empty! \n");
    }
}
int main(int argc, char const *argv[])
{
    circular_queue Q;
    int de_elm;
    init_circular_queue(&Q);
    for (int i = 1; i < 5; i++)
    {
        enqueue(&Q,i*2);
    }
    traverse_circular_queue(Q);
    dequeue(&Q,&de_elm);
    printf("dequeue elem is %d\n",de_elm);
    traverse_circular_queue(Q);
    dequeue(&Q,&de_elm);
    printf("dequeue elem is %d\n",de_elm);
    traverse_circular_queue(Q);
    return 0;
}
