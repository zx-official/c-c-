#include <stdio.h>
 
 int main(){
     int a=123;
     int total=0;
    while(a>0){
        total=total+a%10;
        a=a/10;
        }
    
       printf("%d\n",total);
       return 0;
}
