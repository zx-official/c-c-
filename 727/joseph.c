#include <stdlib.h>
#include <stdio.h>
typedef struct node
{
    int data;
    struct node *next;
}node;
node *head =NULL;
node *create_node(int data)
{
    node *new_node =(node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->next =NULL;
    return new_node;
}
node *find_tail()
{
    node *tail =head;
    if(tail == NULL)
    {
        return tail;
    }
    while (tail->next != NULL)
    {
        tail =tail->next;
    }
    return tail;
}
void insert_node(node *p)
{
    node *tail = find_tail();
    if(tail == NULL)
    {
        head = p;

    }else
    {
        
        tail->next = p;
    }
   
}
void make_loop()
{
     node *tail = find_tail();
      tail->next = head;
}
int sit_problem(int n)
{
    int count = 2;
    for (int i = 1; i <= n; i++)
    {
        node *new_node = create_node(i);
        insert_node(new_node);
    }
    make_loop();
    node *temp = head->next;
    node *pre = head;
    while (temp->next != temp)
    {
        if(count %3 == 0)
        {
            pre->next =temp->next;
            free(temp);
            temp = pre->next;
        }
         count++;
         pre = pre->next;
        temp = temp->next;
    }
    return temp->data;
}
int main(int argc, char const *argv[])
{
    printf("%d",sit_problem(4));
}
