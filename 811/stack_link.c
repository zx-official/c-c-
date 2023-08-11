#include <stdlib.h>
#include <stdio.h>
typedef struct stack_node
{
    int data;
    struct stack_node *next;
}stack_node,*stack_ptr;
void init_stack(stack_ptr *S)
{
    *S = (stack_node * )malloc(sizeof(stack_node));
    if(!S)
    {
        printf("malloc failed ! \n");
        exit(-1);
    }
    (*S)->next =NULL;
}
void push(stack_ptr *S,int target)
{
    stack_node *new_node = (stack_node *)malloc(sizeof(stack_node));
    if(!new_node)
    {
        printf("malloc failed \n");
        exit(-1);
    }
    new_node->data = target; 
    new_node->next = (*S);
    (*S) = new_node;
    
}
void pop(stack_ptr *S,int *pop_elm)
{
    if((*S)->next == NULL)
    {
        printf("stack is empty! \n");
        exit(-1);
    }
    *pop_elm = (*S)->data;
    stack_ptr temp = (*S);
    (*S) = (*S)->next;
    temp->next = NULL;
    free(temp);
}
void clear_stack(stack_ptr *S)
{
    stack_ptr temp;
    while ((*S)!= NULL)
    {
        temp = (*S);
        (*S) = (*S)->next;
        temp->next = NULL;
        free(temp);
    }
    
}
void traverse_stack(stack_ptr S)
{
    if (S ==NULL)
    {
        printf("stack is empty \n");
        
    }
    
    while (S != NULL && S->next !=NULL)
    {
        printf("%d\n",S->data);
        S = S->next;
    }
    
}
int main(int argc, char const *argv[])
{
    
    stack_ptr S;
    init_stack(&S);
    int pop_elm;
    for (int i = 0; i < 4; i++)
    {
        push(&S,i);
    }
    traverse_stack(S);
    pop(&S,&pop_elm);
    printf("pop elem is %d\n",pop_elm);
    traverse_stack(S);
    clear_stack(&S);
    traverse_stack(S);
    return 0;
}
