#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void game() {
    printf("请猜测一个数（1-100）\n");
    srand((unsigned int)time(NULL));
    int num = rand() % 100 + 1;
    int val = 0;
    int i = 1;
    while (1) {
        scanf("%d", &val);
        if (val > 100 || val <= 0) {
            printf("错误，请检查您输入的数\n");
        } else if (val > num) {
            printf("猜的太大了\n");
        } else if (val < num) {
            printf("猜测太小了\n");
        } else {
            printf("恭喜猜对了\n");
            break;
        }
        if (i >= 10) {
            printf("出局\n");
            break;
        }
        printf("当前猜测次数为%d\n", i);
        i++;
    }
}

void tips() {
    printf("继续（1）还是退出(0)？\n");
}

int main() {
    int a = 0;
    while (1) {
        game();
        tips();
        scanf("%d", &a);
        printf("\n");
        if (a != 1)
            break;
    }
    system("pause");
    return 0;
}
