#include <iostream>
#include <string.h>

using namespace std;

class Student;
class  Date
{
private:
	int m_year;
	int m_month;
	int m_day;
public:
	Date(int y = 2001, int m = 1, int d = 1)
	{
		m_year = y;
		m_day = d;
		m_month = m;
		cout << "Date constructor" <<endl;
	}
	~Date()
	{
		cout << "Date destroyer" <<endl;
	}
	void disp()
	{
		cout << m_year << "-" << m_month << "-" <<m_day <<endl;
	}

	void setDate(int y = 2000, int m = 1, int d = 1)
	{
		m_year = y;
		m_day = d;
		m_month = m;
	}
};

class Person
{
	protected:
		char m_name[12];
		int m_age;
		Date m_birthday;
	public:
		Person(const char * name = "Tom", int age = 18)
		{
			m_age = age;
			strcpy(m_name, name);
			cout << "Person constructor" <<endl;
		}
		~Person()
		{ 
			cout << "Person destroy" << endl;
		}

		void disp()
		{
			cout << m_name << " " << m_age <<endl;
			m_birthday.disp();
		}
};

class Student:public Person
{
protected:
	char m_major[12];
public:
	Student(const char *name, int age, const char *major)
	:Person(name, age)
	{
		strcpy(m_major, major);
		cout << "Student construtor" <<endl;
	}

	~Student()
	{
		cout << "Student destroy" << endl;
	}

	void disp()
	{
		cout << m_name<<" " << m_age <<
		" " << m_major  << endl;
	}

	void print()
	{
		cout << m_name<<" " << m_age <<
		" " << m_major  << endl;
	}
};


class PartimeStudent:public Student
{
protected:
	char m_job[12];
public:
	PartimeStudent(const char *name, int age,
					const char *major, const char *job):
						Student(name, age, major)
	{
		strcpy(m_job, job);
		cout << "PartimeStudent constructor" << endl;
	}

	~PartimeStudent()
	{
		cout << "PartimeStudent destroy" << endl;
	}

	void disp()
	{
		cout << m_name<<" " << m_age<<
		" " << m_major <<" " << m_job << endl;
		m_birthday.disp();
	}
};
int main()
{
	PartimeStudent s("Ypw", 18, "EI","Soft Engineer");
	s.disp(); 
	s.Student::disp();
	s.Person::disp();
    return 0;
}
