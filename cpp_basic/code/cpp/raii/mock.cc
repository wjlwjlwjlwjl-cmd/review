#include <iostream>
#include <functional>
using namespace std;

template<class T>
class auto_ptr
{
public:  
    auto_ptr(T* ptr)
        : _ptr(ptr)
    {
        cout << "开始管理资源" << endl;
    }

    auto_ptr(auto_ptr& ptr)
        : _ptr(ptr._ptr)
    {
        ptr._ptr = nullptr;
    }

    auto_ptr& operator=(auto_ptr& ptr)
    {
        if(ptr != *this)
        {
            if(_ptr)
            {
                delete _ptr;
            }
            _ptr = ptr._ptr;
            ptr._ptr = nullptr;
        }
    }

    ~auto_ptr()
    {
        if(_ptr)
        {
            delete _ptr;
            cout << "释放资源" << endl;
        }
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }
private:
    T* _ptr;
};

template <class T>
class unique_ptr
{
public:  
    explicit unique_ptr(T* ptr)
        : _ptr(ptr)
    {
        cout << "开始管理对象" << endl;
    }

    ~unique_ptr()
    {
        if(_ptr)
        {
            cout << "释放对象" << endl;
            delete _ptr;
        }
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& ptr)
        : _ptr(ptr._ptr)
    {
        ptr._ptr = nullptr;
    }

    void operator=(const unique_ptr&& ptr)
    {
        _ptr = ptr._ptr;
        ptr._ptr = nullptr;
    }
private:
    T* _ptr;
};

template <class T>
class shared_ptr
{
public:  
    explicit shared_ptr(T* ptr = nullptr)
        : _ptr(ptr)
        , _pcount(new int(1))
    {
        cout << "开始资源管理" << endl;
    }

    template<class D>
    shared_ptr(T* ptr, D del)
        : _ptr(ptr)
        , _pcount(new int(1))
        , _del(del)
    {}

    shared_ptr(shared_ptr& sp)
    {
        _ptr = sp._ptr;
        _pcount = sp._pcount;
        _del = sp._del;
        (*_pcount)++;
        cout << "当前引用计数为" << *_pcount << endl;
    }

    void release()
    {
        if(--(*_pcount) == 0)
        {
            delete _pcount;
            _del(_ptr);
            cout << "引用计数为0，释放资源" << endl;
            return;
        }
        cout << "当前引用计数为" << *_pcount << endl;
    }

    void operator=(shared_ptr& sp)
    {
        if(_ptr != sp._ptr)
        {
            release();
            _ptr = sp._ptr;
            _del = sp._del;
            _pcount = sp._pcount;
            (*_pcount)++;
            cout << "当前引用计数为" << *_pcount << endl;
        }
    }

    T* get()
    {
        return _ptr;
    }

    T& operator*()
    {
        return *_ptr;
    }

    T* operator->()
    {
        return _ptr;
    }

    int use_count()
    {
        return *_pcount;
    }

    ~shared_ptr()
    {
        release();
    }

private:
    T* _ptr;
    int* _pcount;
    function<void(T* ptr)> _del = [](T* ptr){ delete ptr; };    
};

template<class T>
class weak_ptr
{
public:  
    weak_ptr(T* ptr)
        : _ptr(ptr)
    {}

    weak_ptr(const shared_ptr<T>& sp)
        : _ptr(sp.get())
    {}

    void operator=(const shared_ptr<T>& sp)
    {
        _ptr = sp.get();
    }
private:
    T* _ptr;
};

template<class T>
class DeleteClass
{
public:
    void operator()(T* ptr)  
    {
        cout << "释放资源" << endl;
        delete[] ptr;
    }
};

int main()
{
    int* arr = new int[10];
    // auto_ptr<int> ap1(arr);
    // auto_ptr<int> ap2(ap1);

    // unique_ptr<int> up1(arr);
    // unique_ptr<int> up2(move(up1));
    
    auto Delete = [](int* ptr){delete ptr; cout << "定制删除器释放资源" << endl;};
    shared_ptr<int> sp(arr, DeleteClass<int>());
    cout << "---" << endl;
    shared_ptr<int> sp1(sp);
    cout << "---" << endl;
    shared_ptr<int> sp3;
    cout << "---" << endl;
    sp3 = sp1;
    cout << "---" << endl;

    return 0;
}
