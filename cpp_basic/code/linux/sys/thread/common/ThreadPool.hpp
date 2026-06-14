#include <iostream>
#include <queue>
#include "Cond.hpp"
#include "Logger.hpp"
#include "Mutex.hpp"
#include "Thread.hpp"

template <class T> //有用户自己定义任务的类型
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
            DEBUG("get task: {}", getpid());
            task();
        }
    }

public:  
    ThreadPool(int threadnum)
        : _threadnum(threadnum)
        , _waitnum(0)
        , _isrunning(false)
    {
        DEBUG("ThreadPool construct");
    }

    void Init()
    {
        for(int i = 0; i < _threadnum; i++)
        {
            Thread th(bind(&ThreadPool::HandleFunc, this));
            _threads.push_back(th);
            DEBUG("Init thread {}", th.Name());
        }
    }

    void Start()
    {
        if(_isrunning == true)
        {
            return;
        }
        _isrunning = true;
        for(auto e: _threads)
        {
            e.Start();
            DEBUG("Start thread {}", e.Name());
        }
    }

    void Enqueue(const T& task)
    {
        _mutex.Lock();
        if(_isrunning)
        {
            _tasks.push(task); 
            if(_waitnum > 0)
            {
                _cond.Notify();
            }
        }
        _mutex.UnLock();
    }

    void Stop()
    {
        _isrunning = false;
        _mutex.Lock();
        _cond.NotifyAll();
        _mutex.UnLock();
        DEBUG("清理残余任务，退出中...");
    }

    void Wait()
    {
        for(auto& e: _threads)
        {
            e.Join();
            DEBUG("{} exit", e.Name());
        }
    }
private:
    int _waitnum;
    int _threadnum;
    bool _isrunning;

    queue<T> _tasks;
    vector<Thread> _threads;
    Mutex _mutex;
    Cond _cond;
};
