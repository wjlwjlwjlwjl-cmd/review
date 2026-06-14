#include <iostream>
using namespace std;

template <class T>
class shared_ptr
{
public:  
    shared_ptr(T* ptr)
        : _ptr(ptr)
        , _pcount(new int(1))
    {
        cout << "开始管理资源" << endl;
    }

    shared_ptr(shared_ptr& sp)
    {
        _pcount = sp._pcount;
        (*_pcount)++;
        _ptr = sp._ptr;
        cout << "开始管理资源" << endl;
    }

    void operator=(shared_ptr& sp)
    {
        if(--(*_pcount) == 0)
        {
            delete _pcount;
            delete _ptr;
            cout << "释放资源" << endl;
        }
        _pcount = sp._pcount;
        (*_pcount)++;
        _ptr = sp._ptr;
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }

    ~shared_ptr()
    {
        if(--(*_pcount) == 0)
        {
            delete _ptr;
            delete _pcount;
            cout << "释放资源" << endl;
        }
    }
private:
    T* _ptr;
    int* _pcount;
};

int main()
{
    int* num = new int(0);
    shared_ptr<int> sp(num);
    return 0;
}
