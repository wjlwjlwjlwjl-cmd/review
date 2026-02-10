#include <signal.h>
#include <iostream>

void handler(int signo)
{
    std::cout << "接收到信号: " << signo << std::endl;
}

int main()
{
    signal(SIGSEGV, handler);
    int *pa = NULL;
    *pa = 100;
    return 0;
}
