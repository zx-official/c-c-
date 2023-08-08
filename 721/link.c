#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node
{
    int data;
    struct node *next;
}node;

node *head = NULL;

node *mk_node(int data)
{
    node *p =(node *)malloc(sizeof(node));
    if(p == NULL)
    {
        printf("malloc filed !");
        exit(1);
    }
    p->data = data;
    p->next=NULL;
    return p;
}
void free_node(node *p)
{
    free(p);
}
void insert_node(node *p)
{
    p->next = head;
    head = p ;
}
void print_link()
{
    node *p = head;
    while (p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}
void traverse()
{
	node *p =head;
	while(p != NULL)
	{
		printf("%d ",p->data);
		p = p ->next;
	}
    printf("\n");
}
node *search(int target)
{
    node *p = head;

    while(p != NULL)
    {
        if(p ->data == target)
        {
            return p;
        }
        p =p->next;

    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    int i;
    node *p;
    //srand(time(NULL));
    int target;
    for(i = 0; i <10; i++)
    {
        p =mk_node(rand()%100 +1);
        insert_node(p);        
    }
    traverse();
    scanf("%d",&target);
    p =search(target);
    if(p == NULL)
    {
        printf("can't find !");
    }else
    {
        printf("%p %d %d\n",p,p->data,target);
    }
    return 0;
}
