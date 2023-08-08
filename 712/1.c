#include<stdio.h>

int g_init = 100;
int g_uninit;
static int sg_init = 200;
static int sg_uninit;

void fun()
{
     auto int l_init = 100;
     auto int l_uninit;
    static int sl_init = 200;
    static int sl_uninit;
    printf("g_init:     %p\n",&g_init);
    printf("g_uninit:   %p\n",&g_uninit);
    printf("sg_init:    %p\n",&sg_init);
    printf("sg_uinit:   %p\n",&sg_uninit);
    printf("l_init:     %p\n",&l_init);
    printf("l_uninit:   %p\n",&l_uninit);
    printf("sl_init:    %p\n",&sl_init);
    printf("sl_uninit:  %p\n",&sl_uninit);
    printf("rodata      %p\n","hello,word");
    printf("text:		%p\n", fun);
}
int main()
{
    fun();
}
