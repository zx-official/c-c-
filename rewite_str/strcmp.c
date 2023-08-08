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