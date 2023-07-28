#include<stdio.h>
int main(int argc, char const *argv[])
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int *p =a;
	for (int i = 0; i <= 10; i++)
	{
		*p = i ;
		p++;
	}
		p = a;
		for (int i = 0; i < 20; i++)
		{
			printf("%d ",*p );
			p++;
		}
	return 0;
}
