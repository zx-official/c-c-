#include <stdio.h>
int get_weekday(int y,int m,int d)
{
int week;
//2017年6月18日周日
//Week=(Day + 2*Month + 3*(Month+1）/5 + Year + Year/4 - Year/100 +
//Year/400) % 7
if (m == 1 || m == 2)
{
y = y - 1;
m = m + 12;
}
week = (d + 2 * m + 3 * ( m + 1) / 5 + y + y / 4 - y / 100 + y / 400)%7;
return (week + 1) % 7 ; 
//这个算出来的值周一是0所以要加1，变成周一为1 周六为6,周日为0
}
int is_leap_year(int year)
{
return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
void print_cal(int year)
{
int i;
int j;
int k;
int start_week = 0;
int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
if (is_leap_year(year) == 1)
{
m[1] = 29;
}
for ( i = 0; i < 12; i++)
{
printf("\n------%4d年 %2d月-----\n", year, i + 1);
printf("日 一 二 三 四 五 六\n");
for (j = 0; j < m[i]; j++)
{
    if (j == 0)
{
start_week = get_weekday(year, i + 1, j + 1);
for (k = 0; k < start_week; k++)
{
printf(" ");
}
}
printf("%2d ",j + 1); //正常计算日期的时候是从1号开始计算的
if ((j + 1 + start_week) % 7 == 0)
{
printf("\n");
}
}
printf("\n");
}
}
int main()
{
int year;
printf("请输入年份\n");
scanf("%d",&year);
print_cal(year);
return 0;
}