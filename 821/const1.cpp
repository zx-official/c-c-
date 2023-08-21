# include<iostream>
using namespace std;
class T
{
public:
    const int ci_b;
    int i_a;
    T(int a,int b = 66):ci_b(b)
    {
        i_a = a;
    }
    void show() const
    {
        cout<<"i_a = "<<i_a<<endl;
        cout<<"ci_b ="<<ci_b<<endl;
    }
};
int main(int argc, char const *argv[])
{
    const T a(20);
    a.show();
    return 0;
}
