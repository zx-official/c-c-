# include <iostream>
# include <ctime>
using namespace std;
class MyDate
{
    public :
    MyDate()
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);

        hour = localTime->tm_hour;
        min = localTime->tm_min;
        sec = localTime->tm_sec;
    }
    MyDate(int H,int M,int S)
    {
        hour = H;
        min = M;
        sec = S;
    }
    ~MyDate()
    {

    }
    void print()
    {
        cout<<hour<<":"<<min<<":"<<sec<<endl;

    }
    void formate_print()
    {
        int is_PM = 0;
        int temp_hour = hour;
        if ( hour > 12)
        {
            is_PM = 1;
            temp_hour = hour -12;
        }
        cout<<temp_hour<<":"<<min<<":"<<sec<<(is_PM? "PM":"AM")<<endl;
        
    }
    MyDate operator++()
    {
        sec += 1;
        if (sec >= 60)
        {
            sec -= 60;
            min += 1;
            if (min >= 60)
            {
                min -= 60;
                hour += 1;

            }
        }
        return *this;
    }

    MyDate operator+(const MyDate &D2) const
    {
        int new_hour = hour + D2.hour;
        int new_min = min + D2.min;
        int new_sec = sec + D2.sec;
        if (new_sec >= 60)
        {
            new_sec -= 60;
            new_min += 1;
        }
        if (new_min >= 60)
        {
            new_min -= 60;
            new_hour += 1;
        }

        MyDate result(new_hour,new_min,new_sec);
        return result;
    }



    private:
    int hour;
    int min;
    int sec;
};
int main(int argc, char const *argv[])
{
    MyDate cur;
    cur.print();
    cur.formate_print();

    // MyDate cur(14,50,12);
    // cur.formate_print();
    // cur.print();
    // MyDate temp(2,50,12);
    // temp.formate_print();
    // temp.print();
    // ++temp;
    // temp.print();
    // MyDate result = temp +cur;
    // result.print();

    return 0;
}
