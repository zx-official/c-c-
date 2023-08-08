#include<stdio.h>
 int main()
 {
    const int a = 100;
    printf("%d\n",a);
   int *p = &a;
   *p =250;
    printf("%d\n",a);
    printf("%p\n",&a);
 }

