#include <iostream>
#include <signal.h>

void PrintPending(sigset_t* pending)
{
    std::cout << "cur process[" << getpid() << "]";
    for(int signo = 31; signo >= 1; signo--)
    {
        if(sigismember(pending, signo))
        {
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }
    std::cout << std::endl;
}

void handler(int signo)
{
    std::cout << "received signal" << signo << std::endl;
    sigset_t* pending;
    sigemptyset(pending);
    sigpending(pending);
    PrintPending(pending);
    exit(0);
}

int main()
{
    signal(2, handler);

    sigset_t block_set, old_set;
    sigemptyset(&block_set);
    sigemptyset(&old_set);
    sigaddset(&block_set, 2);
    sigprocmask(SIG_BLOCK, &block_set, &old_set);

    int count = 15;
    while(count--)
    {
        sigset_t pending;
        sigpending(&pending);
        PrintPending(&pending);
        sleep(1);
    }

    std::cout << "解除对2号信号的屏蔽" << std::endl;
    sigprocmask(SIG_SETMASK, &old_set, &block_set);
    return 0;
}
