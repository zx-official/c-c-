#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[])
{
    int i;
    int *p =(int *)malloc(10*sizeof(int));
    if(p == NULL)
    {
        printf("malloc filed \n");
        exit(1);
    }
    for (int i = 0; i < 10; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d",p[i]);
    }
    free(p);
    printf("\n");
    
    return 0;
}
