/*共享内存的相关函数
#include <sys/ipc.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
    - 功能：创建一个新的共享内存段，或者获取一个既有的共享内存段的标识
        新创建的内存段中的数据都会被初始化为0
    - 参数：
        - key： key_t类型是一个整形，通过这个找到或者创建一个共享内存
                一般使用16进制，非0值
        - size：共享内存的大小
        - shmflg：属性
            - 访问权限
            - 附加属性，创建/判断共享内存是不是存在
                IPC_CREATE | IPC_EXCL | 0664
    - 返回值：
            失败返回-1并设置错误号
            成功返回共享内存的引用ID，后面操作共享内存都是通过这个值

void *shmat(int shmid, const void *shmaddr, int shmflg);
    - 功能：和当前的进程进行关联
    - 参数： 
    - shmid：共享内存的标识，有shmget返回值得到
    - shmaddr： 申请的共享内存的起始地址，指定NULL，由内核指定
    - shmflg：对共享内存的操作
        - 读： SHM_RDONLY,必须要有读权限
        - 读写：0
    - 返回值：
        成功返回共享内存的首地址，失败（void*）-1

int shmdt(const void *shmaddr);        
    - 作用：解除当前进程和共享内幕内存的关联
    - 参数：
        shmaddr：共享内存的首地址
    - 返回值：
        成功返回0，失败返回-1

int shmctl(int shmid, int cmd, struct shmid_ds *buf);  
    - 功能：对共享内存的操作，删除共享内存共享内存要删除才会消失，创建共享内存的进程被销毁了对共享内存没有任何影响
    - 参数：
        -shmid：共享内幕才能的首地址
        - cmd： 要做的操作
            - IPC_STAT：获取共享内存的当前的状态
            - IPC_SET： 设置共享内存的状态
            - IPC_RMID: 标记共享内存被销毁
        - buf：结构体指针 表示要设置的属性信息
            - IPC_STAT：buf存储数据
            - IPC_SET： buf中需要初始化数据，设置到内核中
            - IPC_RMID: 没有用，NULL

*/
