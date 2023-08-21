//拷贝构造函数
/*
Stack s1;
Stack s2 = s1; or  Stack s2(s1);
*/
#include<iostream>
#include <string.h>

#define STACK_SIZE 10
using namespace std;
class Stack
{
private:
    int *m_stack;
    int m_top;
public:
    Stack()
    {
        m_stack = new int[STACK_SIZE];
        cout<<"constructed start ..."<<endl;
        m_top = 0;
    }
    ~Stack()
    {
        cout<<"destructed start..."<<endl;
        m_top = 0;
        cout<<"~stack"<<endl;
    }
    Stack(Stack &s)
    {
        m_stack = new int[STACK_SIZE];
        int i;
        for ( i = 0; i < STACK_SIZE; i++)
        {
            m_stack[i] = s.m_stack[i];
        }
        m_top = s.m_top;
        cout<<"deep copy ..."<<endl;
        
    }
    Stack & operator =(const Stack &s)
    {
        int i;
        for ( i = 0; i < STACK_SIZE; i++)
        {
            m_stack[i] = s.m_stack[i];
        }
        m_top = s.m_top;
        cout<<"assignment"<<endl;
        return *this;
    }
    bool is_empty()
    {
        return m_top == 0;
    }
    bool is_max()
    {
        return m_top == STACK_SIZE;
    }
    void push(int item)
    {
        if (!is_max())
        {
            m_stack[m_top++] = item;
        }else
        {
            printf("stack is max\n");
        }       
    }
    int pop()
    {
        if (!is_empty())
        {
            int res = m_stack[--m_top];
            return res;
        }
        else
        {
            printf("stack is empty!\n");
            return -500;
        }
    }

};
int main(int argc, char const *argv[])
{
    Stack *p = new Stack();
    p->push(5);
    p->push(4);
    p->push(3);
    p->push(2);
    p->push(1);
    Stack s2 = *p;
      while (!s2.is_empty()) 
    {
        cout << "Popped: " << s2.pop() << endl;
    }
    while (!p->is_empty()) 
    {
        cout << "Popped: " << p->pop() << endl;
    }
    delete p;
    return 0;
}




