#include<stdio.h>
/*strcmp函数逻辑 挨个比较 全相等返回0，主串大于子串返回大于0的值，如设计为1或比较数字之差，反之则返回负数，如设计为-1或数字之差
有设计缺陷 
1.没有设计长度限制，可能造成指针越界
2.循环条件str!='\0'
当字符串结尾不存在'\0'时，会造成 strcmp 会继续复制内存直到找到null终止符为止，这可能导致未定义的行为。
3.可能存在空指针问题： 如果传递给strcmp的指针参数为NULL，将导致未定义的行为。
*/
int my_strcmp(char *s1,char *s2)
{
    while(*s1 != '\0')
    {
        if(*s1 != *s2)
        {
            break;
        }
        s1++;
        s2++;       
    }
    if(*s1 > *s2)
    {
        return 1;
    }else if(*s1 < *s2)
    {
        return -1;
    }else
    {
        return 0;
    }

}
//与strcmp相比 strncmp 增加了限制长度，可以在给定范围内查询两个字符串是否相等，但其他的问题没有解决
//并且如果给定的n大于c1或c2之一的长度，可能会造成其他后果
int my_strncmp(char *s1,char *s2,int n)
{
    while(*s1 != '\0' && *s2 !='\0')
    {
        if(*s1 != *s2 || --n<= 0)
        {
            break;
        }
        s1++;
        s2++;      
    }
    if(*s1 > *s2)
    {
        return 1;
    }else if(*s1 < *s2)
    {
        return -1;
    }else
    {
        return 0;
    }
}
int main()
{
    char *s1 = "12345"; 
    char *s2 = "12344";
    int result =my_strncmp(s1,s2,0);
    if (result > 0)
    {
        printf("第一个大");
    }else if(result < 0)
    {
        printf("第二个大");
    }else
    {
        printf("一样大");
    }

}
    