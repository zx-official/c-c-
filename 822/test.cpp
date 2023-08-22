#include <iostream>
using namespace std;

class Point
{
	private:
		int x,y;
	public:
		Point(int a, int b)
		{
			x = a;
			y = b;
		}

		void disp()
		{
			cout << "x: " << x << " y: " << y <<endl;
		}
	friend Point operator+ (const Point&, const Point&);
};

Point operator + (const Point& a, const Point& b)
{
		int x = a.x + b.x;
		int y = a.y + b.y;
		return Point(x, y);
}


int main()
{
	Point a(3, 5);
	Point b(4, 6);

	Point c =  operator+(a, b);
	c.disp();

    return 0;
}
