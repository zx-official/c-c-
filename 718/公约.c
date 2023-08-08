#include<stdio.h>
//更相减损法法 公约数
int function_1(int num1,int num2)
{
	int now = 0;
	if(num1 == num2)
	{
		return num1;
	}else if(num1 > num2)
	{
		now = num1 -num2;
		return function_1(now,num2);
	}else if(num1 < num2)
	{
		now = num2 -num1;
		return function_1(now,num1);
	}

}
//辗转相除法
int function_2(int num1,int num2)
{
	int temp = num1%num2;
	if(temp ==0)
	{
		return num2;
	}else
	{
		return function_2(num2,temp);
	}


}
int main(int argc, char const *argv[])
{
	
	int result =function_2(36,20);
	printf("%d\n",result);
	return 0;
}

