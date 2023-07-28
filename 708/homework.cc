#include <stdio.h>
//检测一个数是否是素数
int indentify(int num) {
    if (num < 2) {
        return 0;
    }
    for (int i = 2; i <= num; i++) {
        if (num % i == 0 && i != num) {
            return 0;
        }

    }
    return 1;
}
void group_identify(int min, int max) {
    for (int i = min; i <= max; i++) {
        if (indentify(i) == 1)
            printf("%d\n", i);
    }
}
int main() {
    group_identify(1,100);
}
