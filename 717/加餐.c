#include<stdio.h>
void print_array(int *a,int len)
{
	for(int i = 0;i < len; i++)
	{
		printf("%d ",a[i] );
	}
	printf("\n");	
}
//归并排序和插入排序,将未排序的元素逐个插入到已排序的部分，将元素插入到正确的位置，逐步构建有序序列。
void insert_sort(int *src,int len)
{

	for(int i = 1;i < len; i++)
	{
		int target = src[i];
		for(int j =i; j>0 && target<src[j-1] ; j--)
      	{	
      			src[j] = src[j-1];
      			src[j-1]=target;
      			print_array(src,len);
      	}
	}
}
int main(int argc, char const *argv[])
{
	int unsort[]={1,5,2,3,6,9,10,4};
	int len =sizeof(unsort)/sizeof(unsort[0]);
	print_array(unsort,len);
	insert_sort(unsort,len);
	printf("排序后的结果为：\n");
	print_array(unsort,len);
	return 0;
}