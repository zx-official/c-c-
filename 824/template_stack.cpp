# include<iostream>
using namespace std;
template <class T>
class Stack
{
    public:
        Stack(int  = 10);
        ~Stack()
        {
            delete [] stackptr;
        }
        int push(const T&);
        T& pop();
        int is_empty()
        {
            return top == 0;
        }
        int is_max()
        {
            return top == size-1;
        }
    private:
        int top;
        int size;
        T* stackptr;
};

template <class T>
Stack<T>::Stack(int a) : size(a), top(0)
{
    stackptr = new T[size];
}

template <class T>
int Stack<T>::push(const T& t)
{
    if (!is_max())
    {
        stackptr[top++] = t;
        return 1;
    }else
    {
        return 0;
    }
}

template <class T>
T& Stack<T>::pop()
{
    if(!is_empty())
    {
        return stackptr[--top];
    }
}

int main(int argc, char const *argv[])
{
    Stack<double>* st = new Stack<double>();
    st->push('1');
    st->push('2');
    st->push('3');
    st->push('4');
    st->push('5');
    st->push('6');
    st->push('7');
    st->push('8');
    st->push('9');
    st->push('10');

    while (!st->is_empty())
    {
        cout<<st->pop()<<endl;
    }
    
    return 0;
}
