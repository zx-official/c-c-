#include <stdio.h>

#define N 6

void print_matrix(int m[N][N])
{
    int i;
    int j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%2d ", m[i][j]);
        }
        printf("\n");
    }
}

void magic_matrix(int m[N][N])
{
    int i;
    int n = 1;
    int col;
    int row;

    for (i = 0; i < (N  + 1)/ 2; i++)
    {
        row = i;
        col = i;
        m[row][col] = n;

        for (; col < N - 1 - i; col++)
        {
            m[row][col] = n;
            n++;    
        }

        for (; row < N - 1 - i; row++)
        {
            m[row][col] = n;
            n++;
        }

        for (; col > i; col--)
        {
            m[row][col] = n;
            n++;
        }

        for (; row > i; row--)
        {
            m[row][col] = n;
            n++;
        }
    }
}

int main()
{
    int m[N][N];

    magic_matrix(m);
    print_matrix(m);

    return 0;
}
