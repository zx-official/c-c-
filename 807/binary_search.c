#include <stdio.h>
int binary_search(int *p,int target,int start,int end)
{
    if (start > end) {
        return -1;  // 目标元素不存在，返回 -1
    }
    int mid = (start+end)/2;
    if(p[mid] == target)
    {
        return mid;
    }else if (p[mid] > target)
    {
        return binary_search(p,target,start,mid-1);
    }else if (p[mid] < target)
    {
        return binary_search(p,target,mid+1,end);
    }
    
}
int main(int argc, char const *argv[])
{
    int test[]={2,3,7,9,12,22,31};
    int target = 30;
    int result = binary_search(test,target,0,7);
    if (result == -1)
    {
        printf("没找到该元素\n");
    }else
    {
        printf("%d元素在%d下标下",target,result);
    }
    
    
    return 0;
}
