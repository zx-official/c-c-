#include<stdio.h>

void print_array(char *a,int len)
{
	for(int i = 0;i < len; i++)
	{
		printf("%c\t",a[i] );
	}	
}
// 字符串反转
char *revalse_char(char *src,int len)
{
	for(int i = 0; i <= len/2 ;i++)
	{
		char temp = *(src+i);
		*(src+i) = *(src+len-1-i);
		*(src+len-1-i) =temp;
	}
	return src;
}
//递归版
void factor_reverse_char(char *src, int len)
{
    char *end = src + len - 1;
    if (src < end)
    {
        char temp = *src;
        *src = *end;
        *end = temp;
        factor_reverse_char(src + 1, len - 2);
    }
}

//二分法查找
int Binary_Search(int *src, int begin,int end,int target)
{
	while(begin < end)
	{
		int mid = (end-begin)/2;
		if(src[mid] == target)
		{
			return mid; //返回其索引
		}else if(src[mid] < target)
		{
			begin=mid + 1; 
		}else
		{
			end = mid - 1;
		}
	}
	return -1;
}
//递归法
int factor_Binary_Search(int *src, int begin,int end,int target)
{
	int mid = (end +begin)/2;
	if(src[mid]== target)
	{
		return mid;
	}else if(src[mid] < target)
		{
			return factor_Binary_Search(src,mid+1,end,target); 
		}else
		{
			return factor_Binary_Search(src,begin,mid-1,target); 
		}
		return -1;
}
int main(int argc, char const *argv[])
{
	char src[] ={"1234567"};
	int len = sizeof(src)/sizeof(src[0]);
	//char *res = revalse_char(src,len);
	factor_reverse_char(src,len);
	print_array(src,len);
/*	int array[]={1,2,3,4,5,6,7};
	int len = sizeof(array)/sizeof(array[0]);
	//int index =Binary_Search(array,0,len,2);
	int index2 =factor_Binary_Search(array,0,len,1);
	if(index2 != -1)
	{
		printf("找到了！在%d下标处",index2);
	}else
	{
		printf("没找到！");
	} */
	return 0;
}