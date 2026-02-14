#include <iostream>
#include <sys/types.h>
#include <signal.h>

void handler(int signo)
{
    std::cout << "received signal: " << signo << std::endl;
    exit(0);
}

int main()
{
    pid_t pid;
    signal(SIGINT, handler);
    if((pid = fork()) == 0)
    {
        int i = 10;
        while(i--)
        {
            std::cout << "working..." << std::endl;
            sleep(1);
        }
        exit(0);
    }
    sleep(2);
    kill(pid, SIGINT);
    return 0;
}
