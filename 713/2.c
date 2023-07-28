#include<stdio.h>
/*int *bobble_sort(int * ptr)
{
	int *o_ptr= ptr;
	while(*ptr != null)
	{
		ptr++;
	}
	int length = (ptr-o_ptr)/sizeof(int);
	int *temp = 0;
	for(int i = 0;i < length;i++)
	{
		for(int j =0; j < length-i-1;j++)
		{
			int *next_ptr = ptr + 1；
			if(*o_ptr > *next_ptr)
			{
				temp =o_ptr;
				o_ptr=next_ptr;
				next_ptr=temp;

			}
		}
	}
	return o_ptr;
}
*/
void print_array(int *a,int length)
{
	for(int i = 0 ;i < length; i++)
	{
		printf("%d,",*a);
		a++;
	}
		printf("\n");
}
void bubble_sort_array(int a[],int length)
{
	int temp =0;
	for(int i = 0; i< length; i++)
	{
		for(int j = 0; j<length-i-1;j++)
		{
			if(a[j]<a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
//选择排序是一种简单直观的排序算法，其基本思想是每次从未排序的
//序列中选择最小（或最大）的元素，并将其与未排序序列的第一个元素进行交换，从而逐步构建有序序列。
void select_sort(int a[],int length)
{
	for(int i = 0;i < length-1; i++)
	{
		int index = i;
		for(int j = i+1;j <length;j++)
		{
			if(a[j] < a[index])
			{
				index = j;
			}
		}
			int temp = a[i];
			a[i] = a[index];
			a[index] = temp;
			print_array(a,length);
	}
}
void temp_int (int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp
}
void insert_sort(int *str,int length)
{


}
int main()
{
int a[]={7,6,8,2,1};
//print_array(a,5);
select_sort(a,5);
//bubble_sort_array(a,5);

/*for(int i = 0; i< 5; i++)
{
	printf("%d\n",a[i]);
}*/
}

