#include "task.hpp"
#include <fcntl.h>
#include <unistd.h>

class channel
{
public:  
    channel(pid_t pid, pid_t wfd)
        : _pid(pid)
        , _wfd(wfd)
    {}

    pid_t pid()
    {
        return _pid;
    }

    void send(int cmd)
    {
        write(_wfd, &cmd, sizeof(cmd));
    }
private:
    pid_t _pid;
    pid_t _wfd;
};
