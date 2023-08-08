#include<stdio.h>
#include<string.h>
//I'm from shanghai ! ->shanghai ! from I'm
void strrev_r(char *str, int len)
{
	char tmp;

	if (len <= 1)
	{
		return;
	}

	tmp = *str;
	*str = *(str + len - 1);
	*(str + len - 1) = tmp;

	return strrev_r(str + 1, len - 2);
}
void reverse_words(char* str)
{
    int len = strlen(str);
    strrev_r(str, len); 

    char* word_start = str;
    char* temp_p = str;
    int word_len =0;;

    while (*temp_p != '\0')
    {
        if (*temp_p == ' ')
        {
            strrev_r(word_start, word_len);  // 反转一个单词
            word_start = temp_p+1;  // 更新下一个单词的起始位置
            word_len = 0;
        }else
        {
        	word_len++;
        }
        temp_p++;
     
    }
		//strrev_r(word_start, word_len);
    
}
int main()
{
	char tests[]={" I'm from shanghai!"};
	reverse_words(tests);
	for(int i = 0; i < strlen(tests); i++)
	{
		printf("%c",tests[i] );
	}
}