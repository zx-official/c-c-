#include <stdio.h>
#include <string.h>

int my_strcmp(char *s1, char *s2)
{
    while (*s1 != '\0')
    {
        if (*s1 != *s2)
        {
            break;
        }

        s1++;
        s2++;
    }

    return *s1 - *s2;
}

int my_strncmp(char *s1, char *s2, int n)
{
    int i = 1;

    while (*s1 != '\0' && i < n)
    {
        if (*s1 != *s2)
        {
            break;
        }

        s1++;
        s2++;
        i++;
    }

    return *s1 - *s2;
}

char *my_strstr(char *haystack, char *needle)
{
    int len = strlen(needle);

    while (*haystack != '\0')
    {
        if (strncmp (haystack, needle, len) == 0)
        {
            return haystack;
        }
        haystack++;
    }

    return NULL;
}

int is_palindrome(char *str)
{
    char *begin = str;
    char *end = str + strlen(str) - 1;

    while (begin < end)
    {
        if (*begin != *end)
        {
            return 0;
        }
        begin++;
        end--;
    }

    return 1;
}

char *str_reverse(char *str)
{
    int i;
    int tmp;
    int len = strlen(str);

    for (i = 0; i < len / 2; i++)
    {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }

    return str;
}

char *strn_reverse(char *str, int len)
{
    int i;
    int tmp;

    for (i = 0; i < len / 2; i++)
    {
        tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }

    return str;
}

int word_len(char *str)
{
    int len = 0;
    while (*str != ' ' && *str != '\0')
    {
        len++;
        str++;
    }

    return len;
}

char * itoa(unsigned int x, int scale, char *buf)
{
    int i = 0;
    int low;
    while (x > 0)
    {
        low = x % scale;
        if (low >= 10)
        {
            low = low  - 10 + 'A';
        }else
        {
            low = low + '0';
        }
        buf[i] = low;
        x /= scale;
        i++;
    }
    buf[i] = '\0';
    str_reverse(buf);

    return buf;
}

int str_times(char *str, char *sub)
{
    int len = strlen(sub);
    int total = 0;

    while (*str != '\0')
    {
        if (strncmp (str, sub, len) == 0)
        {
            total++;
            str += len;
        }else
        {
            str++;
        }
        
    }

    return total;
}

char *reverse_sentence(char *str)
{
    int len;
    char *o_str = str;
    str_reverse(str);

    while (*str != '\0')
    {
        while (*str == ' ')
        {
            str++;
        }
        len = word_len(str);
        strn_reverse(str, len);
        str = str + len;
    }

    return o_str;
}

char *find_a_frame(char *str, char *head, char *tail, char *buf)
{
    char *f_head;
    char *f_tail;
    char *begin;
    char *end;
    int i;
    if ((f_head = strstr(str, head)) == NULL)
    {
        return NULL;
    }

    if ((f_tail = strstr(f_head + strlen(head), tail)) == NULL)
    {
        return NULL;
    }

    begin = f_head;
    end = f_tail + strlen(tail);
    i = 0;
    while (begin < end)
    {
        buf[i++] = *begin; 
        begin++;
    }
    buf[i] = '\0';

    return buf;
}

char *rm_x(char *str, char x)
{
    char *r = str;
    char *w = str;

    while (*r != '\0')
    {
        if (*r != x)
        {
            *w++ = *r++;
        }else
        {
           r++; 
        }
    }
    *w = '\0';

    return str;
}

char *rm_other_blank(char *str)
{
    char *r = str;
    char *w = str;
    int is_first;

    while (*r == ' ')
    {
        r++;
    }

    is_first = 1;
    while (*r != '\0')
    {
        if (*r == ' ')
        {
            if (is_first)
            {
                *w++ = *r++;
                is_first = 0;
            }else
            {
                r++;
            }
            
        }else
        {
            *w++ = *r++;
            is_first = 1;
        }
    }

    if(*(w - 1) == ' ')
    {
        *(w - 1) = '\0';
    }else
    {
        *w = '\0';
    }
    
    return str;
}

int main()
{
    char buf[]= "    I     love    China!";

    printf("%s|||\n", rm_other_blank(buf));

    return 0;
}