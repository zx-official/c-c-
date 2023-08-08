#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* str = "     -1234abc";
    int num = atoi(str);
    
    printf("Converted number: %d\n", num);
    
    return 0;
}

