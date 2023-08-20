#include<iostream>
#include <string.h>

#define STACK_SIZE 10
using namespace std;
class Stack
{
private:
    int m_stack[STACK_SIZE];
    int m_top;
public:
    Stack()
    {
        cout<<"constructed start ..."<<endl;
        m_top = 0;
    }
    ~Stack()
    {
        cout<<"destructed start..."<<endl;
        m_top = 0;
        cout<<"~stack"<<endl;
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
      while (!p->is_empty()) 
    {
        cout << "Popped: " << p->pop() << endl;
    }
    delete p;
    return 0;
}




