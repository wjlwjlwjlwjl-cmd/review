#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>

using namespace std;

template <class T>
class block_queue
{
public:
    block_queue(int size = 5)
    {
        pthread_cond_init(&_consumer_cond, NULL);
        pthread_cond_init(&_productor_cond, NULL);
        pthread_mutex_init(&_mutex, NULL);
        _productor_wait_num = 0;
        _consumer_wait_num = 0;
        _size = size;
    }

    bool isFull()
    {
        return _queue.size() == _size;
    }

    bool isEmpty()
    {
        return _queue.empty();
    }

    void push(const T& val)
    {
        pthread_mutex_lock(&_mutex);
        while(isFull())
        {
            cout << getpid() << "当前队列已满，开始等待" << endl;
            _productor_wait_num++;
            pthread_cond_wait(&_productor_cond, &_mutex);
            cout << getpid() << " 生产者等待结束" << endl;
            _productor_wait_num--;
        }
        _queue.push(val);
        if(_consumer_wait_num)
        {
            pthread_cond_signal(&_consumer_cond);
        }
        pthread_mutex_unlock(&_mutex);
    }

    T& pop()
    {
        pthread_mutex_lock(&_mutex);
        while(isEmpty())
        {
            cout << getpid() << "当前队列为空，开始等待" << endl;
            _consumer_wait_num++;
            pthread_cond_wait(&_consumer_cond, &_mutex);
            cout << getpid() << " 消费者等待结束" << endl;
            _consumer_wait_num--;
        }
        T& val = _queue.front();
        _queue.pop();
        if(_productor_wait_num > 0)
        {
            pthread_cond_signal(&_productor_cond);
        }
        pthread_mutex_unlock(&_mutex);
        return val;
    }

    ~block_queue()
    {
        pthread_cond_destroy(&_consumer_cond);
        pthread_cond_destroy(&_productor_cond);
        pthread_mutex_destroy(&_mutex);
    }
private:
    queue<T> _queue;
    int _size;
    pthread_cond_t _consumer_cond;
    pthread_cond_t _productor_cond;
    pthread_mutex_t _mutex;
    int _productor_wait_num;
    int _consumer_wait_num;
};
