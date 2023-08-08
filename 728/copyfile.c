/*

    #include <unistd.h>

    ssize_t read(int fd, void *buf, size_t count);
        参数：
            -fd：文件描述符，靠这个操作文件
            -buf：缓冲区，需要读取数据存放的地方，数据的地址（传出参数）
            count: 数组的大小 
        返回值：
            -成功：
                >0 返回实际读取到的字符值
                =0 文件已经读取完了
            -失败：-1 ，并且设置errno

    #include <unistd.h>
    ssize_t write(int fd, const void *buf, size_t count);
        参数：
            -fd：文件描述符，open得到的，靠这个操作文件
            -buf：要往磁盘中写入的数据
            count: 要写的数据的实际大小 
        返回值：
            -成功：
                >0 返回实际读取到的字符值
                =0 没有任何内容写入
            -失败：-1 ，并且设置errno    
*/
#include <unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc, char const *argv[])
{
    //通过open打开txt文件
    int srcfd = open("english.txt",O_RDONLY);
    if(srcfd == -1)
    {
        perror("open");
        return -1;
    }
    //创建一个新的文件（拷贝文件）
    int destfd = open("spy.txt",O_WRONLY | O_CREAT,0664);
    if(destfd == -1)
    {
        perror("create");
        return -1;
    }
    //频繁的读写操作
    char buf[1024] = {0};
    int len = 0;
    while ((len = read(srcfd,buf,sizeof(buf))) > 0)
    {
        write(destfd,buf,len);
    }
    
    //关闭文件
    close(destfd);
    close(srcfd);
    return 0;
}
