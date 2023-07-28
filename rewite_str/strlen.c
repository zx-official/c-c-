int my_strlen(char *str)
{   
    int total = 0;
    while (*str != '\0')
    {
        total++;
        str++;
    }
    return total;
}