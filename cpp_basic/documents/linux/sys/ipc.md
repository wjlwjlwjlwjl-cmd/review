# 匿名管道
## 产生接口
```cpp
int pipe(int pipefd[2]);
```
返回产生匿名管道的文件描述符，使用系统调用write和read完成对匿名管道的读写
## 读写规则
1. read满时，如果没有定义O_NONBLOCK，就阻塞等待；如果定义了O_NONBLOCK，就返回-1，errno被设置为EAGAIN;
2. write满时，根据是否定义O_NONBLOCK，处理方式与read满时相同
3. 同步规则：一个管道的写端退出时，读端继续读取剩下未读取的数据，读取完继续读取返回EOF；读端退出时，写端继续写会返回-1
4. 写入匿名管道时，如果写入大小小于匿名管道大小，linux系统会保证写入操作的原子性；否则不一定
# 命名管道
## 产生接口
```cpp
int mkfifo(char* pathname, int open_mode);
```
open_mode，与系统调用open的完全相同
<strong>管道，不管是否匿名，都是内存中的一块缓冲区，不过命名管道在目录中能够看到的是内存缓冲区的标识符，即使删除正在使用命名管道的进程也能够使用</strong>
## 读写与使用规则
1. 除了使用open打开命名管道以外，与匿名管道完全相同

# 共享内存
## 共享内存函数
### shmget
```cpp
int shmget(key_t key, size_t size, int shnflg);
```
key，这个共享内存段的名字，size，共享内存的大小，shmflg用法和初见文件使用的mode_t相同
IPC_CREAT | IPC_EXCL，共享内存不存在，创建并返回；若存在，则报错返回
### shmat
```cpp
void* shmat(int shmid, const void* shmaddr, int shmflg);
```
shmid，共享内存地址，就是shmget的返回值，shmaddr共享内存的链接地址，如果给空指针的话，内核会自己选择一块地址；
shmflg，可以取两个值SHM_RND和SHM_RDONLY。<br>
成功返回指向共享内存第一个位置的指针
### shmdt
```cpp
int shmdt(const void* shmaddr)
```
将共享内存与当前进程分离，但是并没哟删除共享内存
### shnctl
```cpp
int shmctl(int shmid, int cmd, struct shmid_ds* buf);
```
shmid，表示进程；cmd表示对进程的操作；buf指向一个包含共享内存信息的结构体
* cmd的取值
1. IPC_STAT，将shmid_ds结构中的数据设置为当前共享内存的关联值，即通过第三个输出型参数来获取共享内存的信息
2. IPC_SET，在进程有足够权限的情况下，将共享内存的属性设置为buf指针提供的结构体中的信息
3. IPC_RMID，删除共享内存（前面的detach是将共享内存和当前进程剥离）
## 查看与删除共享内存
共享内存必须删除，否则除非关机，不然不会清楚，共享内存的生命周期随内核
1. 查看：ipcs -m
2. 删除：ipcrm -m shm_id
3. 共享内存的删除并不是直接删除，而是拒绝后续映射，只有担当当前共享内存的映射计数位0时，才会真正删除这块共享内存
