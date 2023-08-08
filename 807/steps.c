#include <stdio.h>
int steps(int num)
{
    /*最后两步有两种走法 
    一步一步走 前面的台阶头step(n-1)种走法
    两步一起走 前面的台阶有step(n-2)种走法
    总的走法即为step(n-1)+step(n-2)种
    */
    if (num == 1 || num == 2)
    {
        return num;
    }else
    {
        return steps(num-1)+steps(num-2);
    }
    

}
int main(int argc, char const *argv[])
{
    int test =10;
    printf("%d个台阶一共有%d种走法\n",test,steps(test));
    return 0;
}
