#include<stdio.h>
void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
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
void Matrix_transpose(int *a,int row,int col)
{
    int new_martix[row*col];
    int*p = new_martix;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            
            *(new_martix + j*row + i) = *(a + i*col + j);
        }
        
    }
    print_matrix(p,4,3);
}
int main(int argc, char const *argv[])
{ int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int *p =(int *)matrix;
    print_matrix(p,3,4);
    Matrix_transpose(p,3,4);
    return 0;
}
