# include <iostream>
# include <string>
using namespace std;
int main(int argc, char const *argv[])
{
    string str = "helloword";
    for (int i = str.length()-1; i >= 0; i--)
    {
        cout.put(str[i]);
    }
    
    return 0;
}
