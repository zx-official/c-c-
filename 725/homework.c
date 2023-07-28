#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 5
//Append SRC onto DEST
char *my_strcat(char *dest,char *src)
{
    char *o_dest =dest;
    while (*dest != '\0')
    {
        dest++;
    }
    while (*src != '\0')
    {
        *(dest) = *src;
        dest++;
        src++;
    }
    return o_dest;
}
//字符串查找，返回字串和后面的元素
char* my_strstr(char * mainly,char *target)
{
    int len =strlen(target);
    while (*mainly != '\0')
    {
        if (strncmp(mainly,target,len) == 0)
        {
            return mainly;
        }
        
        mainly++;
    }
    return NULL;
}
void print_matrix(int *m,int rol,int cow)
{
    int i;
    int j;
    for (i = 0; i < rol; i++)
    {
        for (j = 0; j < cow; j++)
        {
            printf("%2d ",*(m+i*cow+j));
        }
        printf("\n");
    }
}
void magic_matrix_reverse(int a[N][N])
{   
    //颠倒行列即可
    int n = 1;
    int rol;
    int cow;
    int i;
    for ( i = 0; i < (N+1)/2; i++)
    {
        rol = i; //列
        cow = i; //行
        a[rol][cow] = n;
        for (rol; rol < N-1-i; rol++)
        {
           a[rol][cow] = n;
           n++;
        }
        for (cow; cow < N-1-i; cow++)
        {
           a[rol][cow] = n;
           n++;
        }
        for (rol; rol > i; rol--)
        {
           a[rol][cow] = n;
           n++;
        }
        for (cow; cow > i; cow--)
        {
           a[rol][cow] = n;
           n++;
        }
    }
    
}
void magic_matrix_reverse_de(int a[N][N])
{   
    
    int max = N*N;
    int rol;
    int cow;
    int i;
    for ( i = 0; i < (N+1)/2; i++)
    {
        rol = i; //列
        cow = i; //行
        a[rol][cow] = max;
        for (rol; rol < N-1-i; rol++)
        {
           a[rol][cow] = max;
           max--;
        }
        for (cow; cow < N-1-i; cow++)
        {
           a[rol][cow] = max;
           max--;
        }
        for (rol; rol > i; rol--)
        {
           a[rol][cow] = max;
           max--;
        }
        for (cow; cow > i; cow--)
        {
           a[rol][cow] = max;
           max--;
        }
    }
    
}
void magic_matrix(int a[N][N])
{   
    //
    int n = 1;
    int rol;
    int cow;
    int i;
    for ( i = 0; i < (N+1)/2; i++)
    {
        rol = i; //列
        cow = i; //行
        a[rol][cow] = n;
        for (rol; rol < N-1-i; rol++)
        {
           a[cow][rol] = n;
           n++;
        }
        for (cow; cow < N-1-i; cow++)
        {
           a[cow][rol] = n;
           n++;
        }
        for (rol; rol > i; rol--)
        {
           a[cow][rol] = n;
           n++;
        }
        for (cow; cow > i; cow--)
        {
           a[cow][rol] = n;
           n++;
        }
    }
    
}
void magic_martix_de(int a[N][N])
{
    int max = N*N;
    int col; //列
    int row; //行
    int i;
    for ( i = 0; i < (N+1)/2; i++)
    {
        row = i;
        col = i;
        a[row][col] = max;
        for (col; col < N-1-i; col++)
        {
            a[row][col] = max;
            max--;
        }
        for (row; row < N-1-i; row++)
        {
            a[row][col] = max;
            max--;
        }
        for (col; col > i; col--)
        {
            a[row][col] = max;
            max--;
        }
        for (row; row > i; row--)
        {
            a[row][col] = max;
            max--;
        }
    }
    
}
//交换函数
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
//非方阵的矩阵转置
void Matrix_transpose(int *a,int row,int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j= 0; j < col; j++)
        {
            swap(a+i*col+j,a+j*row+i);
        }
        
    }
    
}

int main(int argc, char const *argv[])
{   


    int test[2][3]={{1,2,3},{4,5,6}};
    int *p=(int *)test;
    Matrix_transpose(p,2,3);
    print_matrix(p,3,2);
    char a[20] ="I love china fovever";
    char b[20] = "china";
    //char *p = my_strcat(a,b);
    //char *test =my_strstr(a,b);
    //printf("%s",test);
    int m[N][N];
    magic_matrix_reverse_de(m);
    print_matrix(m,N,N);
    return 0;
}
