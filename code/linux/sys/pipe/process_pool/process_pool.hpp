#include "channel.hpp"
#include <sys/wait.h>

/*
管道的读写规则
1. write满时
O_NONBLOCK，返回-1，errno为EAGAIN；没有设置，
则阻塞等待
2. read完时，情况与write满时相同
3. read还在，但是写端文件描述符被关闭，读端推出
4. write还在，读端推出，写端可能退出
5. 写入大小不超过pipe_buf大小，linux保持其原子性，否则不一定
*/
class process_pool
{
public:  
    process_pool(int sz)
        : _pool_size(sz)
    {}

    void initPool()
    {
        int num = _pool_size;
        while(num--)
        {
            pid_t fds[2];
            pipe(fds);
            pid_t pid;
            if((pid = fork()) == 0)
            {
                close(fds[1]);                                                           
                dup2(fds[0], 0);
                std::cout << getpid() << std::endl;
                _tm.worker(); //等待任务
                exit(0);
            }
            std::cout << "创建进程池进程" << pid << std::endl;
            close(fds[0]);
            _channels.emplace_back(pid, fds[1]);
        }
    }

    void dispatchTask()
    {
        int n = _pool_size;
        while(n--)
        {
            int task = _tm.getTask();
            auto process = _channels.back();
            _channels.pop_back();
            process.send(task);
            sleep(1);
        }
    }

    void destroyPool()
    {
        for(auto e: _channels)
        {
            int pid = waitpid(e.pid(), nullptr, 0);
            if(pid == e.pid())
            {
                std::cout << "回收" << pid << "进程" << std::endl;
            }
        }
    }
private:
    int _pool_size;
    task_manager _tm;
    std::vector<channel> _channels;
};
