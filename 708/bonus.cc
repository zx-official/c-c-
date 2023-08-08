//企业提成
#include<stdio.h>
double earn(double i) 
{
	double bonus = 0;
	double bonus1 = 100000 * 0.1;
	double bonus2 = bonus1 + 100000 * 0.075;
	double bonus3 = bonus2 + 200000 * 0.05;
	double bonus4 = bonus3 + 200000 * 0.03;
	double bonus5 = bonus4 + 400000 * 0.015;
	if (i <= 100000)
	{
		bonus = i * 0.1;
	}
		else if (i < 200000)
		{
			bonus = bonus1 + (i - 100000) * 0.075;
		
	}
		else if (i < 400000)
		{
		bonus = bonus2 + (i - 200000) * 0.05;
		}
		else if (i < 600000)
	{
		bonus = bonus3 + (i - 400000) * 0.03;
	}
		else if (i < 1000000)
	{
		bonus = bonus4 + (i - 600000) * 0.015;
	}
		else if (i > 1000000)
	{
		bonus = bonus5 + (i - 1000000) * 0.1;
	}
	return bonus;

}
int main() {
	double i=0;
	printf("请输入当月利润:\n");
	scanf("%lf", &i);
	double bonus = earn(i);
	printf("奖金总数为:%lf,\n",bonus);
}
