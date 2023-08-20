#include <iostream>
#include <string.h>
using namespace std;
class Person
{
public:
    char *m_name;
    int m_age;

    Person()
    {
        m_name = new char[100];
        strcpy(m_name,"default");
        m_age = 22;
        cout<<"缺省构造函数 start"<<endl;
    }
    Person(const char * name,int age)
    {
        m_name =new char[100];
        strcpy(m_name,name);
        m_age = age;
        cout<<"构造函数 start"<<endl;
    }
    void setName(const char *name)
    {
        if (m_name != NULL)
        {
            delete []m_name;

        }
        m_name = new char[100];
        strcpy(m_name,name);
    }

    void setAge(int age)
    {
        m_age = age;
    }
    void disp()
    {
        cout<<"Name:"<<m_name<<endl;
        cout<<"Age:"<<m_age<<endl;

    }
    ~Person()
    {
        delete[] m_name;
        cout<<"desturcted ..."<<endl;
    }
};
int main(int argc, char const *argv[])
{
    Person *p = new Person[3];
    p->disp();
    delete [] p;
    // Person *p2 = new Person("Alice",18);
    // p2->disp();
    //Person p1[3];
    

    
    return 0;
}
