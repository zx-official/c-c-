char *my_strcpy(char *dest,char *src)
{
    char *o_dest = dest;
    while (*src != '\0')
    {
        *dest++ = *src++;
    }
    return o_dest;
}