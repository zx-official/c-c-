#include<stdio.h>
int is_leap_year(int year)
{
return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
int get_week(int year,int month,int day)
{
    if(month ==1 || month  ==2)
    {
        year =year -1;
        month = 12 +month;
    }
    int week=(day + 2*month + 3*(month+1)/5 + year + year/4 - year/100 + year/400) % 7;
    return (week + 1)%7;
}
void print_year(int year)
{
    int month_day[]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(is_leap_year(year) == 1)
    {
        month_day[1] = 29;
    }
    for( int i = 0; i < 12; i++)
    {   printf("\n");
        printf("-----%d年 %d月----\n",year,i+1);
        printf("日 一 二 三 四 五 六\n");
        int week = get_week(year, i + 1, 1);
        for (int j = 0; j < week; j++) \
        {
            printf("   "); 
        }
        for (int  j = 0; j < month_day[i]; j++)
        {
            if(week % 7 == 0)
            {
                printf("\n");
            }
            printf("%2d ",j+1);
            week++;
        }
        
    }
}
int main(int argc, char const *argv[])
{
    int year;
    scanf("%d",&year);
    print_year(year);
    return 0;
}
