#include <stdio.h>
int get_sum(int num){
    
     int total=0;
    while(num>0){
        total=total+num%10;
        num=num/10;
        }
    return total;
}
 int main()
 {
       printf("%d\n",get_sum(1234));
       return 0;
}
