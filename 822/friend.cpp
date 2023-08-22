#include <iostream>
#include <math.h>
using namespace std;
class Point
{
public:
    Point(double i, double j){ x=i; y=j;}
    void getxy() { cout<<"("<<x<<","<<y<<")"<<endl; }
    friend double my_distance(Point a, Point b); //友元函数的说明
private:
    double x,y;
};

double my_distance(Point a, Point b) 
{ //友元函数的定义
    double dx=a.x-b.x;
    double dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}
int main(){
    double d11=3.0,d12=4.0,d21=6.0,d22=8.0;
    Point P1(d11,d12),P2(d21,d22);
    P1.getxy(); P2.getxy();
    double d = my_distance(P1,P2); //友元函数的调用
    cout<<"Distance is "<<d<<endl;
return 0;
}