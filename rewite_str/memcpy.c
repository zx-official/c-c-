void *my_memcpy(void *dest,  void *src, int n)
{   
    int i;
    char *p = (char *)dest;
    char *q = (char *)src;
    for ( i = 0; i < n; i++)
    {
        p[i] = q[i];
    }
    return src;
}