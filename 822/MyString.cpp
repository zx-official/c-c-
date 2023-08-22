#include <iostream>
using namespace std;
class MyString
{
    public:
    MyString();
    MyString(char *sz);
    MyString(const MyString & other);
    MyString & operator =(const MyString &rhs);
    ~MyString();
    int assign(const char *);
    void display();
    int repalce(const char *from,const char * to);
    int append(const char *);
private:
    char *m_data;
    unsigned int m_len;
};