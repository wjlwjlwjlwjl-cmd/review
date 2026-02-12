#include <cstdint>
#include <iostream>
#include <pthread.h>
#include <functional>
#include <unistd.h>
using namespace std;

enum TStatus
{
    T_NEW,
    T_RUN,
    T_STOP  
};
using tfunc_t = function<void()>;
static uint16_t cnt = 0;

class Thread
{
public:  
    Thread(tfunc_t run)
        : _run(run)
        , _status(T_NEW)
        , _joinable(true)
    {
        Setname();
    }

    void EnableDetach()
    {
        if(_status == T_NEW)
        {
            _joinable = false;
        }
    }

    void EnableJoin()
    {
        if(_status == T_NEW)
        {
            _joinable = true;
        }
    }

    void Start()
    {
        if(_status == T_RUN)
        {
            return;
        }
        pthread_create(&_pid, NULL, _Start, (void*)this);
    }

    void Join()
    {
        if(_joinable)
        {
            pthread_join(_pid, NULL);
        }
    }

    string Name()
    {
        return _name;
    }
private:
    void Setname()
    {
        _name = "Thread" + to_string(cnt++);
    }

    static void* _Start(void* arg)
    {
        Thread* pt = static_cast<Thread*>(arg); 
        pthread_setname_np(pthread_self(), pt->_name.c_str());
        pt->_status = T_RUN;
        if(pt->_joinable == false)
        {
            pthread_detach(pthread_self());
        }
        pt->_run();
        return nullptr;
    }
private:
    string _name;
    pthread_t _pid;
    TStatus _status;
    tfunc_t _run;
    bool _joinable;
};
