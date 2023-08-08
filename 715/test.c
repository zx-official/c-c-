#include<stdio.h>
#include<assert.h>
void add_test()
{
	static char ch ='a';
	char *cp =&ch;
	printf("%c\n",(*cp)++ );

}
int find_char( char **strings,int value)
{
	assert(strings != NULL);
	while( *strings != NULL)
	{
		if(*(*strings)++ == value)
		{
			return 1;
		}
		strings++;
	}
	return 0;
}
int main()
{
    char strings[] = {"I", "am", "a", "Chinese", "man", NULL};
    char target = 'a';

    if (find_char(strings, target)) {
        printf("找到字母了！\n");
    } else {
        printf("没有找到！\n");
    }
	return 0;
}