#include <iostream>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void* rout(void* arg)
{
    int i = 10;
    while(i--)
    {
        std::cout << "I am thread" << pthread_self() << "\n" << std::endl;
        sleep(1);
    }
    // int ret;
    // pthread_exit(&ret);
}

int main()
{
    int ret = 0;
    pthread_t tid;
    if((ret = pthread_create(&tid, NULL, rout, NULL)) != 0)
    {
        fprintf(stderr, "pthread_create:%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int i = 5;
    while(i--)
    {
        std::cout << "i am main thread\n" << std::endl;
        sleep(1);
    }
    pthread_cancel(tid);
    return 0;
}
