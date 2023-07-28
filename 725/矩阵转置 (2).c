#include <stdio.h>

void print_martix(int *a,int row,int col)
{
    int i;
    int j;

    for(i = 0;i < row;i++)
    {
        for(j = 0;j < col;j++)
        {
            printf("%2d ",(*(a + i * col + j)));
        }
        printf("\n");
    }
}

void swap(int *a,int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_martix(int *a,int row,int col)
{
    int i,j;
    int rev[row*col];
    for(i = 0;i < row;i++)
    {
        for(j = 0;j < col;j++)
        {
            
            *(rev + j*row + i) = *(a + i*col + j);
        }
    }

    for(i = 0;i < row*col;i++)
    {
        a[i] = rev[i];
    }
    
}

int main(int argc, char const *argv[])
{
    int a[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int a_rev[12];

    //reverse_martix(a,3,4);
    //print_martix(a,4,3);
    reverse_martix(a,2,6);
    print_martix(a,6,2);

    return 0;
}
