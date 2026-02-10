#include <iostream>
#include <signal.h>

void handler(int signo)
{
    std::cout << "received exit signal" << std::endl;
    sleep(1);
    exit(0);
}

int main()
{
    signal(SIGINT, handler); //自定义捕捉一个信号
    while(1)
    {
        std::cout << "working" << std::endl;
        sleep(1);
    }
    return 0;
}
