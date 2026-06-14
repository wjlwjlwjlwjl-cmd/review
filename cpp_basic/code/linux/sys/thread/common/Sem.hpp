#pragma once
#include <semaphore.h>

class Sem
{
public:  
    Sem(int sz)
    {
        sem_init(&_sem, 0, sz); //第二个参数__pshared==0，则信号量用于线程间的同步，否则用于进程间的同步 
    }

    void P()
    {
        sem_wait(&_sem); //--
    }

    void V()
    {
        sem_post(&_sem); //++
    }

    ~Sem()
    {
        sem_destroy(&_sem);
    }
private:
    sem_t _sem;
};
