# include <iostream>
using namespace std;
class Shape
{
    public:
        virtual void area()
        {
            cout<<"base area"<<endl;
        }
        virtual void print()
        {
            cout<<"base print"<<endl;
        }
        Shape()
        {
            cout<<"It's a base shape"<<endl;
        }
        virtual ~Shape()
        {
            cout<<"base shape is died"<<endl;
        }
};
class Circle:public Shape
{
    public:
        Circle(int r = 0)
        {
            radius = r;
            cout<<"It's circle"<<endl;
        }
        ~Circle()
        {
            cout<<"Circle is died"<<endl;
        }
        void area() override
        {
            cout<<"circle areas is "<<radius*3.14<<endl;
        }
        void print() override
        {
            cout<<"circle radius is "<<radius<<endl;
        }
    private:
        double radius;
};
class Rectangle:public Shape
{
    public:
    Rectangle(int a = 0,int b = 0)
    {
        len = a;
        wid = b;
    }
    ~Rectangle()
    {
        cout<<"Recentangle is died"<<endl;
    }
    void area() override
        {
            cout<<"circle areas is "<<len*wid<<endl;
        }
        void print() override
        {
            cout<<"recentagle len is "<<len<<endl;
            cout<<"recentagle wid is"<<wid<<endl;
        }

    private:
    int len;
    int wid;

};
int main(int argc, char const *argv[])
{
    Shape *s = new Circle(2);
    s->area();
    s->print();
    delete s;
    return 0;
}