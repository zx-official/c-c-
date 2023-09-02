# include <iostream>
using namespace std;
class complex
{
    private:
    double real,imag;
    public:
    complex(double r = 0,double i =  0):real(r),imag(i)
    {

    };
    friend ostream& operator<<(ostream & os,const complex &c);
};
ostream & operator<<(ostream & os,const complex &c)
{
    os<<c.real<<"+"<<c.imag<<"i";
    return os;
}
int main(int argc, char const *argv[])
{
    complex c(3,5);
    int n = 220;
    cout<<c<<","<<n;
    return 0;
}

