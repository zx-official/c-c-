#include<stdio.h>
#include "functional.h"
int main(int argc, char const *argv[])
{
    char buf[20];
    int test =12345;
    printf("%o\n",test);
    itoa(test,8,buf);
    printf("%s\n",buf);
    char a[]="I love china forever!";
    char head[] = "head";
    char tail[] = "tail";
    word_reverse(a,my_strlen(a));
  // char *p = is_leagl(a,head,tail);
    my_print_array(a);
    //printf("%d",my_strlen(a));
    return 0;
}
