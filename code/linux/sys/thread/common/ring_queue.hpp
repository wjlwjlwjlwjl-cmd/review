#include "Sem.hpp"
#include <pthread.h>
#include <unistd.h>
#include <vector>

using namespace std;

template <class T>
class ring_queue
{
private:
    void Lock(pthread_mutex_t* mutex)
    {
        pthread_mutex_lock(mutex);
    }

    void UnLock(pthread_mutex_t* mutex) 
    {
        pthread_mutex_unlock(mutex);
    }
public:  
    ring_queue(int cap = 3)
        : _cap(cap)
        , _pro_sem(cap)
        , _con_sem(0)
        , _pro_step(0)
        , _con_step(0)
    {
        pthread_mutex_init(&_pro_mutex, nullptr);
        pthread_mutex_init(&_con_mutex, nullptr);
        _queue.resize(cap);
    }

    void push(const T& val)
    {
        Lock(&_pro_mutex);
        _pro_sem.P();
        cout << "生产者获得信号量，开始生产" << endl;
        _queue[_pro_step++] = val;
        _pro_step %= _cap;
        UnLock(&_pro_mutex);
        _con_sem.V();
    }

    T& pop()
    {
        Lock(&_con_mutex);
        _con_sem.P();
        cout << "消费者获得信号量，开始消费" << endl;
        T& ret = _queue[_con_step++];
        _con_step %= _cap;
        UnLock(&_con_mutex);
        _pro_sem.V();
        return ret;
    }

    ~ring_queue()
    {
        pthread_mutex_destroy(&_pro_mutex);
        pthread_mutex_destroy(&_con_mutex);
    }
private:
    vector<T> _queue;
    int _cap;
    int _cur;
    pthread_mutex_t _pro_mutex;
    pthread_mutex_t _con_mutex;
    Sem _pro_sem;
    Sem _con_sem;
    int _pro_step;
    int _con_step;
};
