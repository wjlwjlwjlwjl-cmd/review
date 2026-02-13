#include "Cond.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"
#include "Logger.hpp"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <class T>
class ThreadPool
{
private:
    void HandleFunc()
    {
        while(1)
        {
            _mutex.Lock();
            while(_tasks.empty() && _isrunning)
            {
                _waitnum++;
                _cond.Wait(_mutex);
                _waitnum--;
            }
            if(_tasks.empty() && !_isrunning)
            {
            
                _mutex.UnLock();
                break;
            }
            T task = _tasks.front();
            _tasks.pop();
            _mutex.UnLock();
            task();
        }
    }

public:  
    ThreadPool(int threadnum)
    {
        _threadnum = threadnum;
        _waitnum = 0;
        _isrunning = false;
    }

    void Init()
    {
        for(int i = 0; i < _threadnum; i++)
        {
            _threads.emplace_back(bind(&ThreadPool::HandleFunc, this));
            DEBUG("create thread{}", _threads.back().Name());
        }
    }

    void Start()
    {
        _isrunning = true;
        for(auto& e: _threads)
        {
            e.Start();
            DEBUG("run thread: ", e.Name());
        }
    }

    void Stop()
    {
        _isrunning = false;
        _mutex.Lock();
        _cond.NotifyAll();
        _mutex.UnLock();
        DEBUG("stoping all threads...");
    }

    void Wait()
    {
        for(auto& e: _threads)
        {
            e.Join();
            DEBUG("destroy thread {}", e.Name());
        }
    }

    void Enqueue(T task)
    {
        _mutex.Lock();
        if(_isrunning)
        {
            _tasks.push(task);
            if(_waitnum > 0)
            {
                _cond.Notify();
            }
            DEBUG("tasks size{}", _tasks.size());
        }
        _mutex.UnLock();
    }
private:
    vector<Thread> _threads;
    queue<T> _tasks;
    Mutex _mutex;
    Cond _cond;
    int _waitnum;
    int _threadnum;
    bool _isrunning;
};
