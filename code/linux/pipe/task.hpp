#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <functional>

using task_t = std::function<void()>;

class task_manager
{
public:  
    task_manager()
    {
        _tasks.emplace_back([](){std::cout << "task1" << std::endl;});
        _tasks.emplace_back([](){std::cout << "task2" << std::endl;});
        _tasks.emplace_back([](){std::cout << "task3" << std::endl;});
        _tasks.emplace_back([](){std::cout << "task4" << std::endl;});
        srand(time(0));
    }

    int getTask()
    {
        return rand() % _tasks.size();
    }
    void worker()
    {
        while(1)
        {
            int cmd = 0;
            int n = read(0, &cmd, sizeof(cmd));
            if(n == 0)
            {
                std::cout << getpid() << " exit..." << std::endl;
                break;
            }
            else if(n > 0)
            {
                execute(cmd);
            }
            else
            {
                std::cout << "read fail" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    void execute(int cmd)
    {
        std::cout << "有进程" << getpid() << "执行";
        _tasks[cmd]();
    }
private:
    std::vector<task_t> _tasks;
};

