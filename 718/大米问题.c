#include<stdio.h>
#include <math.h>
int rice(int num)
{
	unsigned int total = 0;
	for(int i = 0; i< num; i++)
	{
		total+=pow(2,i);
	}
	return total;
}
int main(int argc, char const *argv[])
{
	printf("%d\n", rice(30));
	return 0;
}