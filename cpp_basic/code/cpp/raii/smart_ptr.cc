#include <iostream>
#include <string>
using namespace std;

template<class T>
class smart_ptr
{
public:  
    smart_ptr(T* ptr)
        : _ptr(ptr)
    {
        cout << "获取资源" << endl;
    }

    T& operator[](int pos)
    {
        return _ptr[pos];
    }

    T* operator->()
    {
        return _ptr;
    }

    T& operator*()
    {
        return *_ptr;
    }

    ~smart_ptr()
    {
        cout << "释放资源" << endl;
        delete[] _ptr;
    }
private:
    T* _ptr;
};

int main()
{
    int* arr = new int[10];
    smart_ptr<int> sp(arr);
    for(int i = 0; i < 10; i++)
    {
        sp[i] = i;
    }
    cout << *sp << endl;
    return 0;
}
