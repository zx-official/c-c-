#include <stdio.h>
int main(int argc, char const *argv[])
{
	int a = 100;
	{
		printf("%d\n",a );
		int a =200;
		printf("%d\n",a);
	}

	return 0;
}
