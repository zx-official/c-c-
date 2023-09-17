#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n == 1 || n ==0)
    {
        return 1;
    }
    else return n * factorial(n-1);
}
int main(int argc, char const *argv[])
{
    cout<<"factorial 7 is"<<factorial(7)<<endl;
    cout<<"factorial 4 is"<<factorial(4)<<endl;
    return 0;
}
