#include<stdio.h>
char *strrev(char *str, int len)
{

	char *max = str +len-1;

	for(int i = 0;i <len/2;i++)
	{
		char temp = *str;
		*str = *max;
		*max = temp;
		str++;  
        max--;  
	}
	return str;
}
//递归处理字符串逆序
char *strrev_factor(char *str, int len)
{
	
}	
int refactor_fibo(int n )
{
	 if(n == 1 || n == 2)
	 {
	 	return n;
	 }
	 return refactor_fibo(n-1)+refactor_fibo(n-2);
}int iter_fibo(int n)
{
	int step1;
	int step2;
	int total;

	if(n == 1 || n ==2)
	{
		return n;
	}
	step1 = 0;
	step2 = 1;
	for(int i =2; i <= n; i++)
	{
		total = step1+step2;
		step1 = step2;
		step2 = total;
	}
	return total;
}
 int add(int a ,int b)
 {
 	int total;
 	total = a+b;
 	return total;
 }
 //归并排序
 // 合并两个有序数组
/*void merge(int arr[], int left, int right) 
{
	//把数组分成左右两部分
	int n1=

}*/
 long factors(int n)
 {
 	if(n == 1)
 	{
 		return 1;
 	}
 	else
 	{
 		long result = n* factors(n-1);
 		return result;
 	}
 	
 }
 int main(int argc, char const *argv[])
 {
 	//printf("%d\n",add(3,5) );
 	//printf("%ld\n",factors(20) );
 	//printf("%d\n",refactor_fibo(4) );
 	//printf("%d\n",iter_fibo(4) );
 	char a[]={"hello"};
 	int len =sizeof(a)/sizeof(char);
 	char *reval =strrev(a,len);
 	for(int i = 0; i <len;i++)
 	{
 		printf("%c\t",a[i] );
 	}
 	return 0;
 }