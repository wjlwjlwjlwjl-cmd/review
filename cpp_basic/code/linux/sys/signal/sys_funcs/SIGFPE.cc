#include <signal.h>
#include <iostream>

void handler(int signo)
{
    std::cout << "接收到信号: " << signo << std::endl;
}

int main()
{
    signal(SIGFPE, handler);
    int a = 10;
    int b = a / 0;
    return 0;
}
/*
硬件异常
会触发响应信号，比如非法内存访问，出发SIGSEGV；除零错误，SIGFPE。这些信号被状态和控制寄存器记录着，虽然执行了我们的自定义捕捉行为，但是在这个类似于位图的结构中
异常的记录一直存在，所以会一直在打印“接收到信号。。。”
*/
