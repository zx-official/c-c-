#include <stdio.h>
char* my_strcpy(char *dest,char *src)
{
	char *o_dest =dest;
	while(*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest ='\0';
	return o_dest;
}
char* my_strncpy(char *dest,char *src,int n)
{
	char* o_dest=dest;
	while(*src != '\0' && n >0)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	//*dest = '\0';
	return o_dest;
}
int main(int argc, char const *argv[])
{
	char a[10]={"helloworda"};
	char b[5]={"12345"};
	printf("%s\n",my_strncpy(a,b,5) );
	return 0;
}