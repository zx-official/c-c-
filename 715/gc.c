#include<stdio.h>
char *find_char (char const *source,char const *chars)
{
	//先判断是否有空参数传入
	if(source == NULL || chars == NULL)
	{
		return NULL;
	}
	char *source_point;
	//外层循环是chars向后移动
	for(source;*source != '\0';source++ )
	{
		for(chars;*chars != '\0';chars++)
		{
			if(*chars == *source && *chars != ' ')
			{
				return (char*)chars;
			}
			
		}
		return NULL;
	}
}
int main()
{;
	const char* source = "i am chinese man";
	const char* chars = "haha man";
	char *result = find_char(source,chars);
	if(*result)
	{
		 printf("%c\n", *result);
	}else
	{
		printf("没找到！");
	}
}