#include <stdio.h>
typedef struct student 
{
int id;
char name[10];
int age;
char sex;
struct student *next;
}student_t;   //重定名 加上typedef即可和不同变量一样 不用初始化时添加struct
student_t *head =NULL;
void print_student(student_t *s)
{
	 printf("%d %s %d %c\n",s->id,s->name,s->age,s->sex);

}
void traverse()
{
	student_t *p =head;
	while(p != NULL)
	{
		print_student(p);
		p = p ->next;
	}
}
int main()
{
 student_t s1={1,"张三",19,'m'};
 student_t s2={3,"李四",19,'f'};
  head = &s1;
  s1.next =&s2;
  s2.next = NULL;
  traverse();

}