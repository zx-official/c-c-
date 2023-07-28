/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode);
    参数：
        -pathname：要打开的文件绝对路径
        -flag:文件的操作权限和其他设置 
            必选项：O_RDONLY, O_WRONLY, or O_RDWR
            可选项：O_CREAT   文件不存在创建新文件
        -mode: 八进制的数，表示创建出的新文件的操作权限 rwx 分别的大小为 4 2 1 7正好是八进制的满
        例如 0777 0代表八进制 775 
        正常代表代表权限为 -rwx-rwx-rwx-
        但文档中注明：the mode of the created file is (mode & ~umask).
        他要经过一个转换 正常用户的umask为0002 root为0022
        0777 -> 0111 0111 0111
    & 0775   -> 0111 0111 0101
    ->0111 0111 0101 =775
    umask的作用：抹去某些权限 抹去其他组的写权限
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char const *argv[])
{
    int fd = open("create.txt",O_RDWR | O_CREAT,0777);
    if (fd == -1)
    {
        perror("create");
    }
    close(fd);
    
    return 0;
}
