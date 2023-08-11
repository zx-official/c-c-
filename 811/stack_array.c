#include <stdio.h>
#define STCAK_SIZE 6
int stack[STCAK_SIZE];
int top = 0;
int is_full()
{
    return (top == STCAK_SIZE);
}
int is_empty()
{
    return top == 0;
}
void push(int data)
{
    if(!is_full())
    {
        stack[top] = data;
        top++;
    }
}
int pop()
{
    return stack[--top];
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        push(i);

    }
    while (!is_empty())
    {
        printf("%d\n",pop());
    }
    
    return 0;
}
