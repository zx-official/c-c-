# include<iostream>
using namespace std;
class Point 
{
private:
    int x;
    int y;
public:
    Point(int a,int b)
    {
        x = a;
        y = b;
    }
    Point operator +(Point &t)
    {
        int a = this->x + t.x;
        int b = this->y + t.y;
        return Point(a,b);
    }
    void show()
    {
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
    }

};
int main(int argc, char const *argv[])
{
    Point a(2,3),b(2,5);
    (a+b).show();
    return 0;
}
