#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct node
{
    int data;
    struct node *left,*right;
}node;

node *stack[512];
int top = 0;

void init_stack()
{
    top = 0;
}

void push(node *p)
{
    stack[top++] = p; 
}
node *pop()
{
    return stack[--top];
}

int is_empty()
{
    return top ==0;
}
 
node *root = NULL;

node *mk_node(int data)
{
    node *p =(node*)malloc(sizeof(node));
    if (p == NULL)
    {
        printf("malloc falied!\n");
        exit(1);
    }
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
    
}
void free_node(node *p)
{
    free(p);
}

//插入节点（迭代法）
void insert_node_n(int item)
{
    node *pre;
    node *parent;
    node *p =mk_node(item);
    parent = pre = root;

    while (pre != NULL)
    {
        parent = pre;
        if(pre->data > p->data)
        {
            pre = pre->left;
        }else if (pre->data < p->data)
        {
            pre = pre->right;
        }else if (pre->data == p->data)
        {
            free_node(p);
            return ; 
        }
        
        if (parent->data > p->data)
        {
            parent->left = p;
        }else 
        {
            parent->right = p;

        }
    }
}

//递归插入
void insert_node_r(node *current, node *p)
{
    if (p->data > current->data)
    {
        if (current->right == NULL)
        {
            current->right = p;
        }else
        {
            insert_node_r(current->right, p);
        }
    }else if (p->data < current->data)
    {
        if (current->left == NULL)
        {
            current->left = p;
        }else
        {
            insert_node_r(current->left, p);
        }
    }else
    {
        free_node(p);
    }
}

void insert_node(int data)
{
    node *p =mk_node(data);
    if (root == NULL)
    {
        root = p;
    }else 
    {
        insert_node_r(root,p);
    }
        
}
void pre_order_traverse()
{
    node *p =root;
    node *right;
    init_stack();
    if (root == NULL)
    {
        return; 
    }
    do
    {
        printf("%d ",p->data);

        right = p->right;

        if (right != NULL)
        {
            push(right);
        }
        p = p->left;

        if (!is_empty() && p == NULL)
        {
            p = pop();
        }
       
    } while (p != NULL);
        
}
void my_pre_order()
{
    if(root == NULL)
    {
        return ;
    }
    init_stack();
    node *p = root;
    while (p != NULL || !is_empty())
    {
        while (p != NULL)
        {
            printf("%d ",p->data);
            push(p);
            p = p->left;
        }
        p =pop();
        p = p->right;
    }   
}

//中遍历
void my_in_order()
{
    node *p = root;
    init_stack();
    while (p != NULL || !is_empty())
    {
        while (p != NULL)
        {
            push(p);
            p = p->left;
        }
        if (!is_empty())
        {
            p = pop();
            printf("%d ",p->data);
            p = p->right;
        }
        
    }
     
}
#define MAX_NODE 50
// 后遍历
void post_order_traverse()
{
    node *s1[MAX_NODE]; //保存节点指针
    node *p = root;
    int s2[MAX_NODE]; //s2存放节点的状态 0 节点赞不能访问  1 节点可以被访问
    int top = 0;
    int is_empty_stack = 1;
    
    if(root == NULL)
    {
        printf("Binary Tree is Empty\n");
        return ;
    }

    do 
    {
    while (p != NULL)
    {
        s1[++top] = p;
        s2[top] = 0;
        p = p->left;
        is_empty_stack = 0;
    }
    //查看s1中是否还有节点
    if (top == 0)
    {
        is_empty_stack = 1;

    }else if (s2[top] == 0)
    {
        p = s1[top]->right;
        s2[top] = 1;
    }else 
    {
        p = s1[top];
        top--;
        printf("%d ",p->data);
        p = NULL;
    }
    }while (!is_empty_stack);
    
}

int max(int a, int b)
{
    return a > b? a : b;
}
int max_depth(node *root)
{
    int left_depth;
    int right_depth;
    if (root == NULL)
    {
        return 0;
    }
    left_depth = max_depth(root->left);
    right_depth = max_depth(root->right);

    return max(left_depth,right_depth)+1;
}
node *search_node(node *current,int data)
{
    if (current == NULL)
    {
        return NULL;
    }
    
    if (current->data == data)
    {
        return current;
    }
    if(current->data > data)
    {
        return search_node(current->left,data);
    }else 
    {
        return search_node(current->right,data);
    }
    
}

void level_order_traverse()
{
    int front = 0;
    int rear = 0;
    node *queue[MAX_NODE];
    node *p = root;

    if (root == NULL)
    {
        printf("binary tree is empty \n");
        return ;
    }
    queue[rear++] = p;
    while (front != rear)
    {
        p = queue[front++];
        printf("%d ",p->data);
        if (p->left != NULL)
        {
            queue[rear++] = p->left;
        }
        if (p->right != NULL)
        {
            queue[rear++] = p->right;
        }
        

    }
    
    


}

int main(int argc, char const *argv[])
{
        int item;
#if 1
    insert_node(20);
    insert_node(10);
    insert_node(26);
    insert_node(6);
    insert_node(16);
    insert_node(24);
    insert_node(30);
    insert_node(3);
    insert_node(5);
    insert_node(8);
    insert_node(7);
    insert_node(12);
    insert_node(18);
    insert_node(22);
    insert_node(25);
    insert_node(28);
    insert_node(32);
#endif

#if 0
    insert_node(5);
    insert_node(2);
    insert_node(10);
    insert_node(3);
    insert_node(9);
    insert_node(20);
#endif
    pre_order_traverse();
    printf("\n");

    my_pre_order();
    printf("\n");

    my_in_order();
    printf("\n");

    post_order_traverse();
    printf("\n");

    level_order_traverse();
    return 0;
}

