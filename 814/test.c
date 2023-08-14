#include <stdio.h>
#include <stdlib.h>
typedef struct t_node {
    int data;
    struct t_node *lchild, *rchild;
} t_node, *t_node_ptr;

t_node_ptr root = NULL;

t_node_ptr mk_t_node(int data) {
    t_node_ptr new_node = (t_node_ptr)malloc(sizeof(t_node));
    if (new_node == NULL) {
        printf("malloc failed !\n");
    }
    new_node->data = data;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void insert_t_node(t_node *root,t_node *target) 
{
    if (root == NULL)
    {
        root = target;
    }else if (root->data == target->data)
    {
        free(target);
    }else if (root->data > target->data)
    {
        insert_t_node(root->rchild,target);
    }else if (root->data < target->data)
    {
        insert_t_node(root->lchild,target);
    }
}

void traverse_m(t_node_ptr root) {
    if (root == NULL) 
    {
        return;
    }
    traverse_m(root->lchild);
    printf("%d ", root->data);
    traverse_m(root->rchild);
}
void traverse_b(t_node_ptr root) {
    if (root == NULL) 
    {
        return;
    }
    printf("%d ", root->data);
    traverse_m(root->lchild);
    traverse_m(root->rchild);
}

int main(int argc, char const *argv[]) {
    //t_node_ptr root = NULL;
    t_node_ptr new1 = mk_t_node(2);
    t_node_ptr new2 = mk_t_node(4);
    t_node_ptr new3 = mk_t_node(6);
    t_node_ptr new4 = mk_t_node(1);
    insert_t_node(root, new1);
    insert_t_node(root, new2);
    insert_t_node(root, new3);
    insert_t_node(root, new4);
    traverse_m(root);
    printf("\n");
    traverse_b(root);
    return 0;
}
