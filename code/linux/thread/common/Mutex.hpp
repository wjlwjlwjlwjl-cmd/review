#pragma once
#include <pthread.h>

class Mutex
{
public:  
    Mutex()
    {
        pthread_mutex_init(&_mutex, nullptr);
    }

    void Lock()
    {
        pthread_mutex_lock(&_mutex);
    }

    void UnLock()
    {
        pthread_mutex_unlock(&_mutex);
    }

    pthread_mutex_t* GetOriginal()
    {
        return &_mutex;
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&_mutex);
    }
private:
    pthread_mutex_t _mutex;
};

class Lock_Guard
{
public:  
    Lock_Guard(Mutex& mutex)
        : _mutex(mutex)
    {
        _mutex.Lock();
    }

    ~Lock_Guard()
    {
        _mutex.UnLock();
    }
private:
    Mutex& _mutex;
};
