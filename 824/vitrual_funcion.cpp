#include <iostream>

using namespace std;

class Point
{
public:
    Point(int x, int y)
    {
    	m_x = x;
    	m_y = y;
	}
    virtual void print() const;
protected:
    int m_x, m_y;
};

void Point::print()const{
   cout << "[" << m_x << "," << m_y<< "]" << endl;
}

class Point3D:public Point
{
public:
    Point3D(int x, int y, int z);
    void print()const;
private:
    int m_z;
};

Point3D::Point3D(int x,int y,int z):Point(x,y)
{
    m_z = z;
}

void Point3D::print() const
{
    cout << "[" << m_x << "," << m_y
            << "," << m_z << "]" << endl;
}

//void fun(Point &s)     结果将如何？
void fun(Point &s)
{
    s.print();
}

int main()
{
  Point3D p(3,4,5);
  p.print();
  fun(p);
  return 0;
}
