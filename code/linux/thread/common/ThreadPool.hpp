#include <iostream>
#include <queue>
#include "Cond.hpp"
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
                cout << getpid() << "开始等待" << endl;
                _waitnum++;
                _wait.Wait(_mutex);
                _waitnum--;
            }
            if(_tasks.empty() && !_isrunning)
            {
                _mutex.UnLock();
                break;
            }
            auto task = _tasks.front();
            _tasks.pop();
            _mutex.UnLock();
            cout << getpid() << "get a task:";
            task();
        }
    }

public:  
    ThreadPool(int threadnum)
        : _threadnum(threadnum)
        , _waitnum(0)
        , _isrunning(false)
    {
        // _threads.resize(threadnum);
        cout << "Thread Pool construct" << endl;
    }

    void Init()
    {
        for(int i = 0; i < _threadnum; i++)
        {
            Thread t(bind(&ThreadPool::HandleFunc, this));           // 
            _threads.push_back(t);
            cout << "初始化线程" << t.Name() << endl;
        }
    }

    void Start()
    {
        _isrunning = true;
        for(auto e: _threads)
        {
            e.Start();
            cout << "启动线程" << e.Name() << endl;
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
                _wait.Notify();
            }
        }
        _mutex.UnLock();
    }

    void Stop()
    {
        _mutex.Lock();
        _isrunning = false;
        _wait.NotifyAll();
        _mutex.UnLock();
        cout << "清理残余任务，退出中..." << endl;
    }

    void Wait()
    {
        for(auto e: _threads)
        {
            e.Join();
        }
        cout << "等待完成，退出" << endl;
    }
private:
    int _waitnum;
    int _threadnum;
    bool _isrunning;

    queue<T> _tasks;
    vector<Thread> _threads;
    Mutex _mutex;
    Cond _wait;
};
