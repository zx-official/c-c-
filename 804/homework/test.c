#include <stdio.h>
#include<stdlib.h>
#include<string.h>
void readmartix(FILE *fp,int martix[3][3])
{
    //定义缓冲区，传入的二维数组会被修改做真实的返回值
    char buf[64];

    //跳过begin行
    fgets(buf,sizeof(buf),fp);
    for (int i = 0; i < 3; i++)
    {
        fgets(buf,sizeof(buf),fp);
        sscanf(buf,"%d %d %d",&martix[i][0],&martix[i][1],&martix[i][2]);
    }

    //跳过end行
    fgets(buf,sizeof(buf),fp);
}
void addmartix(int martix1[3][3],int martix2[3][3],int martix3[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            martix3[i][j] = martix1[i][j] + martix2[i][j];
        }
        
    }
    
}
void writemartix(FILE *fp,int martix[3][3])
{
    //写入begin
    char *begin="begin\n";
    fputs(begin,fp);
    for (int i = 0; i < 3; i++)
    {
        fprintf(fp,"%d %d %d \n",martix[i][0],martix[i][1],martix[i][2]);
    }
    //写入end
    char *end="end\n";
    fputs(end,fp);
   
}
int main(int argc, char const *argv[])
{
    //打开工作
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
    //定义缓冲区
    int martix1[3][3];
    int martix2[3][3];
    int result[3][3];
    readmartix(fp1,martix1);
    readmartix(fp2,martix2);
    addmartix(martix1,martix2,result);
    writemartix(fp3,result);

   //关闭
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);
    return 0;
}