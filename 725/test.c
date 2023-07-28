#include <stdio.h>

void print_matrix(int *a, int row, int col)
{
    int i;
    int j;

    for (i = 0;i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%2d ", *(a + i * col + j));
        }
        printf("\n");
    }
}

void swap(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_matrix(int *a, int row, int col)
{
    int i;
    int j;

    for (i = 0;i < row; i++)
    {
        for (j = i + 1; j < col; j++)
        {
            swap(a + i * col + j, a + j * col + i);
        }
    }
}

int main()
{
    int a[2][5] = {1,2,3,4,5,6,7,8,9,10};

    print_matrix((int *)a, 2, 5);
    reverse_matrix(a, 2, 5);
    print_matrix(a, 5, 2);

    return 0;
}