#include <iostream>
using namespace std;
class Test
{
    private:
    int m_a;
    mutable int  mc_b;
    public:
    Test(int b):mc_b(b)
    {
        cout<<"B="<<mc_b<<endl;
    }
    void setb(int target) const
    {
        this->mc_b = target;
    }
    void show() const
    {
        cout<<"b="<<mc_b<<endl;
    }
};
int main(int argc, char const *argv[])
{
    const  Test a(10),b(20);
    a.setb(23);
    a.show();
    return 0;
}
