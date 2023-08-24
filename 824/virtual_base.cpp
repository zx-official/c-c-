#include <iostream>

using namespace std;

class A
{
public:
    A(const char *s)
    {
    	cout<<"A"<<endl;
	}
    ~A()
    {
    	cout<<"destroy A"<<endl;
	}
};

class B:virtual public A
{
public:
    B(const char *s1,const char *s2):A(s1)
    {
    	cout<<"B"<<endl;
	}
    ~B(){cout<<"destroy B"<<endl;}

    void fun()
    {
    	cout<<"B::fun()"<<endl;
    }
};

class C:virtual public A
{
public:
    C(const char *s1,const char *s2):A(s1)
    {
    	cout<<"C"<<endl;
	}
    void fun()
    {
    	cout<<"C::fun()"<<endl;
	}
    ~C()
    {
    	cout<<"destroy C"<<endl;
	}
};

class D:public B,public C
{
public:
	D(const char *s1,const char *s2,const char *s3,const char *s4)
	:B(s1,s2),C(s2,s3),A(s1)
	{
		cout<<"D"<<endl;
	}
	~D()
	{
		cout<<"destroy D"<<endl;
	}
};

class E:public D
{
public:
	E(const char *s1,const char *s2,const char *s3,const char *s4, const char *s5)
	:D(s1, s2, s3, s4),A(s1)
	{
		cout << "E" <<endl;
	}
	~E()
	{
		cout<<"destroy E"<<endl;
	}
};
int main()
{
    E *ptr = new E("class A","class B","class C","class D", "class E");
    ptr->B::fun();
    delete ptr;
    D *pd = new D("class A","class B","class C","class D");

    delete pd;
    C *pc = new C("class A","class C");
    delete pc;
    return 0;
}

