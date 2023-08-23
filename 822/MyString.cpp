#include <iostream>
#include <string.h>
using namespace std;
class MyString
{
    public:
    MyString();
    MyString(const char *sz);
    MyString(const MyString & other);
    MyString & operator =(const MyString &rhs);
    ~MyString();
    int assign(const char *);
    void display() const;
    int repalce(const char *from,const char * to);
    int append(const char *);
private:
    char *m_data;
    unsigned int m_len;
};
 MyString::MyString()
{
    m_data = new char[1];
    m_data[0] = '\0';
    m_len = 0;
}
MyString::MyString(const char *sz)
{
    int size = strlen(sz)+1;
    m_data = new char[size];
    strcpy(m_data,sz);
    m_len = strlen(sz);
}
MyString::MyString(const MyString &o)
{
    cout<<"deep copy construct"<<endl;
    m_data = new char [o.m_len];
    strcpy(m_data,o.m_data);
    m_len = o.m_len;
}
MyString::~MyString()
{
    delete []m_data;
    cout<<"string is release"<<endl;
}
void MyString::display() const
{
    cout<<m_data<<endl;
    cout<<m_len<<endl;
}
MyString& MyString::operator= (const MyString &rhs)
{
    int new_len = strlen(rhs.m_data)+1;
    char *new_data = new char[new_len];
    strcpy(new_data,rhs.m_data);
    delete [] m_data;
    m_data = new_data;
    m_len = new_len;
    return *this;
}
int MyString::assign(const char * a)
{
    delete []m_data;
    m_data = new char[strlen(a)+1];
    strcpy(m_data,a);
    m_len = strlen(a);
    return m_len;
}
int MyString::append(const char * add)
{
    int len = m_len +strlen(add);
    char temp[m_len + 1];
    strcpy(temp,m_data);
    delete []m_data;
    m_data = new char[len];
    strcpy(m_data,temp);
    strcat(m_data,add);
    m_len = strlen(m_data);
    return m_len;
}
int MyString::repalce(const char *from,const char * to)
{

    char *o_m_data =m_data;
    char *index = strstr(m_data,from);
    if (index != nullptr)
    {
    char  from_len = strlen(from);
    char to_len = strlen(to);
    int new_len = m_len -from_len + to_len;
    char *new_data =new char [new_len+1];
    char *new_p =new_data;
    while (index != NULL)
    {
        strncpy(new_p,m_data,index - m_data);
        new_p += index -m_data ;

        strcpy(new_p,to);
        new_p +=to_len;

        m_data = index +from_len;
        index = strstr(m_data,from);
    }
        strcpy(new_p,m_data); 
        delete [] o_m_data;
        m_data = new_data;
        m_len = new_len;
        return 0;
    }
    return -1;
}
int main(int argc, char const *argv[])
{
    // MyString m("abc123");
    // m.display();
    // MyString n("ac13");
    // n.display();
    // MyString a("");
    // a.display();
    // // test deep copy and function "assign"
    // MyString c(n);
    // c.display();
    // c.assign("hahaha");
    // c.display();
    // n.display();
    // c.append("123");
    // c.display();
    // c = n;
    // c.display();
    MyString src("abbcbbbabcca");
    src.display();
    src.repalce("ab","haha");
    src.display();
    return 0;
}
