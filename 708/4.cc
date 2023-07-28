#include<stdio.h>
int get_count(int min,int max,int index){
int total=0;
int current=min;
while(current<=max){
    int temp=current;
while(current>0)
{
   if(current%10==index)
   {
       total++;
    }
    temp/=10;
}
 current++;
}
return total;
}
int main(){
    printf("%d\n",get_count(1,100,9));
    return 0;
    }
