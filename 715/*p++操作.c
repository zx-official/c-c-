

#include <stdio.h>
void rt()
{
      int num = 0x12345678;
    unsigned char* bytePtr = (unsigned char*)&num;

    printf("Byte 0: 0x%02X\n", bytePtr[0]);
    printf("Byte 1: 0x%02X\n", bytePtr[1]);
    printf("Byte 2: 0x%02X\n", bytePtr[2]);
    printf("Byte 3: 0x%02X\n", bytePtr[3]);

}
void tete(){
    int nums[] = {10, 20, 30, 40};
    int* intPtr = nums;  // 指向数组的第一个元素
    printf("%d",*(intPtr+1));
    //输出20的低字节
    char* nextBytePtr = (char*)(intPtr+1);
    char nextByteValue = *(nextBytePtr+4);
    printf("%c",nextByteValue);
}
void left()
{
char str[] = "hello";
char *p = str;

*p++ = 'H';
printf("%s\n", str);  // 输出 "Hello"
*p = 'E';
printf("%s\n", str);
}

void right(){
    char str[] = "hello";
    char *p = str;
    char c = *p++;
    printf("%c\n", c);  // 输出 'h'
    printf("%c\n", *p);  // 输出 'e'
}
int main(int argc, char const *argv[])
{
    rt();   
}