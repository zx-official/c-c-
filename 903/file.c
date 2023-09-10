# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
int main(int argc, char const *argv[])
{
    char buf[100];
    int result;
    int fd = open("1.txt",O_CREAT| O_RDONLY,0664);
    if (fd < 0 )
    {
        perror("open");
        exit(1);
    }
    while((result = read(fd,buf,sizeof(buf))) > 0)
    {
        //fd 1 is std::out;
        //haha
        write(1,buf,result);
    } 
    close(fd);
    return 0;
}
