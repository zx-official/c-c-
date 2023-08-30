#include <iostream>
#include <algorithm>
#include <functional>
#include <deque>
using namespace std;
int main(int argc, char const *argv[])
{

    deque<int> myDeque;
    deque<int>::iterator it = myDeque.begin();

    myDeque.push_back(1);
    myDeque.push_back(2);
    myDeque.push_back(3);
    myDeque.push_back(1);
    myDeque.push_back(9);
    // for ( const int & num : myDeque)
    // {
    //     cout<<num<<" ";
    // }
    for(it;it != myDeque.end();++it)
    {
        cout<<*it<<" ";
    }
    return 0;
}
