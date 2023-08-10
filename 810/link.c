//1. O(1)时间删除节点
#include "link.h"
#include <assert.h>
#include <stdlib.h>
linknode *creat_node(int data)
{
    linknode *new_node =(linknode *)malloc(sizeof(linknode));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void delteNode(linknode *target)
{
    assert(target != NULL);
    assert(target->next != NULL);
    target->data = target->next->data;
    linknode *temp = target->next;
    target->next = target->next->next;
    free(temp);
    
}
//循环递归
linknode *reverse_linklist(linknode *head)
{
    if(head->next ==NULL || head == NULL)
    {
        return head;
    }
    linknode *next = NULL;
    linknode *pre = NULL;
    while (head != NULL)
    {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}
linknode *recursion_reverse(linknode *head)
{
    if (head == NULL || head ->next == NULL)
    {
        return head;
    }
    linknode * newhead = recursion_reverse(head->next);
    head->next->next = head;
    head->next = NULL;

    return newhead; 
}
//求linklist的倒数第k个节点
linknode *lash_k_node(linknode *head,int k)
{
    linknode *fast = head;
    linknode *slow =head;
    int i = k;
    for (;i >0 && fast != NULL; i--)
    {
        fast = fast->next;
    }
    if (i > 0)
    {
        return NULL;
    }

    while (fast != NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }
    
    
}
//The mid of Linklist
linknode *mid_of_linklist(linknode *head)
{
    linknode *fast,*slow;
    fast = slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
//存在环
int hasloop(linknode *head,linknode **loop_node)
{
    linknode *fast,*slow;
    fast = slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow =slow->next;
        if (fast == slow)
        {
            *loop_node = fast;
            return 1;
        }
        
    }
    return -1;
}
// find entry of the loop
linknode *find_entry_loop(linknode *head)
{
    linknode *fast,*slow;
    fast = slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            break;
        }
    }
    if (fast != slow)
    {
        return NULL;
    }
    
    //exist loop
    fast = head;
    while (fast != slow)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
    
}
// 判断相交
int identify_intersect(linknode *L1,linknode *L2)
{
    while (L1->next !=NULL)
    {
        L1 = L1->next;
    }
    while (L2 ->next != NULL)
    {
        L2 = L2->next;
    }
    if (L1 ==L2)
    {
        return 1;
    }else 
    {
        return -1;
    }   
}
// 链表有环，如何判断相交
int isIntersectwithloop(linknode *l1,linknode *l2)
{
    linknode * circlenode1,*circlenode2;
    if(hasloop(l1,&circlenode1) == -1)
    {
        return -1;
    }
    if(hasloop(l2,&circlenode2) == -1)
    {
        return -1;
    }
    linknode *temp = circlenode2->next;
    while (temp != circlenode2)
    {
        if (temp == circlenode1)
        {
            return 1;
        }
        
        temp = temp->next;
    }
    return -1;


}
linknode *find_intersect_node(linknode *l1,linknode *l2)
{
    int len1 = 0;
    int len2 = 0;
    while (l1->next != NULL)
    {
        len1++;
        l1 = l1->next;
    }
    while (l2->next != NULL)
    {
        len2++;
        l2 = l2->next;
    }
    int dif;
    if (len1 > len2)
    {
        dif = len1 - len2;
        for (int i = 0; i < dif; i++)
        {
            l1 = l1->next;
        }
        
    }else
    {
        dif = len2 -len1;
        for (int i = 0; i < dif; i++)
        {
            l2 = l2->next;
        }
    }
    while (l1 !=NULL)
    {
        if (l1 ==l2)
        {
            return l1;
            l1 = l1->next;
            l2 = l2->next;
        }
        
    }
    return NULL;
    

int main(int argc, char const *argv[])
{
    
    return 0;
}
