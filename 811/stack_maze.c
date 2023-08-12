#include <stdio.h>
#define MAX_ROW 5
#define MAX_COL 5
int maze[MAX_ROW][MAX_COL]=
{
0,1,0,0,0,
0,1,0,1,0,
0,0,0,1,0,
0,1,1,1,0,
0,0,0,1,0,
};
typedef struct point
{
    int row;
    int col;
}point;
//声明全局栈
point stack[512];
int top = 0;
void push (point p)
{
    stack[top++] = p;
}
point pop ()
{
    return stack[--top];
}
void print_maze()
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int is_empty ()
{
    return  top == 0;
}
void visit(int row,int col)
{
    point visited = {row,col};
    maze[visited.row][visited.col] = 2;
    push(visited);
}
void slove_problem (point start,point end)
{
    maze[start.row][start.col] = 2;
    push(start);
    while (!is_empty())
    {
        point cur = pop();
        if (cur.col == end.col && cur.row == end.row)
        {
            printf("找到了！\n");
            break;
        }
        if (maze[cur.row][cur.col+1] ==0 &&cur.col+1 < MAX_COL)
        {
            visit(cur.row,cur.col+1);
        }
        if (maze[cur.row+1][cur.col] ==0 &&cur.row+1 < MAX_ROW)
        {
            visit(cur.row+1,cur.col);
        }
        if (maze[cur.row][cur.col-1] ==0 &&cur.col-1 >= 0)
        {
            visit(cur.row,cur.col-1);
        }
        if (maze[cur.row-1][cur.col] ==0 &&cur.row-1 >= 0)
        {
            visit(cur.row-1,cur.col);
        }
        print_maze();
    }
    printf("没找到！\n");
}
int main(int argc, char const *argv[])
{
    print_maze();
    point start = {0,0};
    point end = {4,4};
    slove_problem(start,end);
    return 0;
}
