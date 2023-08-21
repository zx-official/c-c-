#include<iostream>
using namespace std;
class M
{
public:
    static int ms_b;
    int m_a;
public:
    M(int a)
    {
        m_a = a;
        ms_b += m_a;
    }
    static void f1(M m);
    M (M &o)
    {
        m_a = o.m_a;
        ms_b += o.m_a;
    }
};
int M::ms_b = 0;
void M::f1(M m)
{
    cout<<"A="<<m.m_a<<endl;
    cout<<"B="<<ms_b<<endl;
}
int main(int argc, char const *argv[])
{
    M P(5),Q(10); //ms_b =15
    M::f1(P);       // 注意此处为拷贝构造函数 ms_b =15 +P.m_a(5) = 20;
    M::f1(Q);
    cout<<M::ms_b<<endl;
    return 0;
}

