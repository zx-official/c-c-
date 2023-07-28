#include<stdio.h>
//打印无符号二进制数字
void print_bin(unsigned int x)
{
    unsigned int mask = 1u;
    int i;
    for(i = 31; i>= 0;i--)
    {
        if((mask<<i) & x)
        {
            printf("1");
        }else
        {
            printf("0");
		}
	}
    printf("\n");
}
//一个字节中被置1的位的个数
int countbit(unsigned int x)
{
	unsigned int mask = 1u;
    unsigned int total = 0;
    while (x > 0)
    {
        total += x & mask;
        x >>= 1;
	}
    return total;
}
//输入一个整数a，在输入两个整数p1,p2,将改整数的二进制表示方法中从右端开始的p1到p2位后输出
void output_bin(unsigned int x,int p1,int p2)
{
	int diff =p2 -p1+1;
	if(p1 > 32 || p2 > 32)
	{
		printf("参数错误！");
	}else
	{
		print_bin((x >>p1-1) & ~(~0u <<diff));
	}
} 

//输入一个整数a，在输入两个整数p1,p2,将改整数的二进制表示方法中从右端开始的p1到p2位后取反输出
void output_reverse_bin(unsigned int x,int p1,int p2)
{

	int diff =p2 -p1+1;
	if(p1 > 32 || p2 > 32)
	{
		printf("参数错误！");
	}else
	{
		print_bin(~(x >>p1-1) & ~(~0u <<diff));
	}
}

void settings_bin(unsigned int x,int p,int v)
{
	if((v != 0 && v != 1) || p < 0 || p > 32)
	{
		printf("参数错误！");
	}else
	{
	print_bin(x & ~(1u <<p-1)| (v <<p-1));
	}
}

//循环右移
unsigned int ror2(unsigned int x,int n)
{
    while(n < 0)
    {
        n += 32;
    }
    n = n %32;
	return (x<<(32-n)) + (x>>n);
}

//输入一个32位的整数a，使用按位异^运算，生成一个新的32位整数b，
//使得该整数b的每一位等于原整数a中该位左右两边两个bit为的异或结果。
unsigned int new_number(unsigned int x)
{
		return ror2(x,1)^ror2(x,-1);
}
int main(int argc, char const *argv[])
{
	unsigned int test = 15; //15的二进制代码为1111；
	unsigned int a =0x12345;
	printf("%d",countbit(test)); 
	printf("\n");
	output_bin(a,1,16);
	printf("\n");
	output_reverse_bin(a,1,16);
	printf("\n");
	settings_bin(test,2,0);
	print_bin(new_number(0x12345678));   // 0001 0010 0011 0100 0101 0110 0111 1111->1010 1101 
	return 0;
}
