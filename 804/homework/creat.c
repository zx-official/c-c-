#include <stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[])
{
    FILE *fp1 = fopen("text1.txt", "r");
    if (fp1 == NULL) {
        perror("open1");
        exit(0);
    }

     FILE *fp2 = fopen("text2.txt", "r");
    if (fp2 == NULL) {
        perror("open2");
        exit(0);
    }

     FILE *fp3 = fopen("text3.txt", "w+");
     if (fp3 == NULL) {
        perror("open3");
        exit(0);
    }

    char martix1[3][32] = {{0}};
    char martix2[3][32] = {{0}};
    char martix3[3][32] = {{0}};
    char nothing[64];
    char (*ptr)[32];
    char (*ptr2)[32];
    ptr = martix1;
    ptr2 = martix2;
    // 把begin跳过
    fgets(nothing, sizeof(nothing), fp1);
    fgets(nothing, sizeof(nothing), fp2);
    for (int i = 0; i < 3; i++)
    {
        fgets(*ptr, sizeof(*ptr), fp1);
        fgets(*ptr2, sizeof(*ptr2), fp2);
        ptr++;
        ptr2++;
    }

    ptr = martix1; // 重置指针
    ptr2 = martix2;
    for (int i = 0; i < 3; i++)
    {
        fputs(*ptr, stdout);
        ptr++;     
    }
    for (int i = 0; i < 3; i++)
    {
        fputs(*ptr2, stdout);
        ptr2++;     
    }
        for(int i = 0; i < 3;i++)
    {
        for (int j = 0; j < 32; j++)
        {
            martix3[i][j] = martix1[i][j] + martix2[i][j];
        }
        for (int i = 0; i < 3; i++)
        {
            fputs(*ptr, stdout);
            ptr++;     
        }
        
    }
    fputs("begin",fp3);
    for (int i = 0; i < 3; i++)
    {
        int num1,num2,num3;
        sscanf(martix1[i],"%d %d %d",&num1,&num2,&num3);
        fprintf(fp3,"%d %d %d\n",num1,num2,num3);
    }
    
    fputs("end",fp3);
    // 将结果输入到fp3流中
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
    return 0;
}