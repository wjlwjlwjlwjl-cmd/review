#include <iostream>
#include <pthread.h>
#include <unistd.h>

void* func(void*)
{
    pthread_detach(pthread_self());
    std::cout << "分离线程" << std::endl;
    sleep(2);
    std::cout << "线程退出" << std::endl;
}

int main()
{
    pthread_t pid;
    pthread_create(&pid, NULL, func, NULL);

    sleep(1); //先分离，在等待
    int ret = pthread_join(pid, NULL);
    if(ret == 0)
    {
        std::cout << "线程等待成功" << std::endl;
    }
    else
    {
        std::cout << "线程等待失败" << std::endl;
    }

    return 0;
}
