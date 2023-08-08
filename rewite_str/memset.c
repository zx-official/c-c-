void *my_memset(void *src,int value,int len)
{
    char *p =(char *)src;
    for (int  i = 0; i < len; i++)
    {
        *p = value;
        p++;
    }
    return src;
}