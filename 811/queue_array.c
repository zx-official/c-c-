#include <stdio.h>
#define QUE_SIZE 5
int queue[QUE_SIZE];
int front = 0;
int rear = 0;
int is_full()
{
    return (rear+1)%QUE_SIZE == front;
}
int is_empty()
{
    return rear == front;
}
void enqueue(int data)
{
    if(!is_full())
    {
        queue[rear] = data;
        rear = (rear+1)% QUE_SIZE;
    }
}
int dequeue()
{
    if(!is_empty())
    {
        int data = queue[front];
        front = (front+1)% QUE_SIZE;
        return data;

    }
}
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 4; i++)
    {
        enqueue(i);
    }
    while (!is_empty())
    {
        printf("%d\n",dequeue());
    }
    for (int i = 0; i < 4; i++)
    {
        enqueue(i*2);
    }
    while (!is_empty())
    {
        printf("%d\n",dequeue());
    }
    return 0;
}
