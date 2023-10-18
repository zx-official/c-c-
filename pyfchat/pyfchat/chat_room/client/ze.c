#include <stdio.h>
#include <string.h>

int main()
{
    char buf[1000];
    read(0, buf, 1000);
    *(buf + strlen(buf)) = '\0';
    printf("%s\n",buf);
}
