#include <iostream>
#include <assert.h>

template<class T>
class vector
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;

    vector() = default;

    vector(vector<T>& v)
    {
        reserve(v.capacity());
        for(int i = 0; i < v.size(); i++)
        {
            push_back(v[i]);
        }
    }

    vector(T* first, T* last)
    {
        while(first != last)
        {
            push_back(*first);
            first++;
        }
    }

    vector(size_t num, const T& val = T())
    {
        while(num--)
        {
            push_back(val);
        }
    }

    void insert(iterator pos, const T& val)
    {
        printf("%p %p\n", _start, pos);
        assert(pos >= _start);
        assert(pos <= _end);
        if(_end == _end_of_storage)
        {
            reserve(capacity() == 0 ? 4 : 2 * capacity());
        }

        iterator cur = _end - 1;
        while(cur >= pos)
        {
            *(cur + 1) = *cur;
            cur--;
        }
        _end++;
        *pos = val;
    }

    void erase(iterator pos)
    {
        assert(pos >= _start);
        assert(pos <= _end_of_storage);
        iterator cur = pos;
        while(cur != _end)
        {
            *cur = *(cur + 1);
            cur++;
        }
        _end--;
    }

    vector& operator=(vector& v)
    {
        clear();
        for(int i = 0; i < v.size(); i++)
        {
            push_back(v[i]);
        }
        return *this;
    }

    void swap(vector& v)
    {
        std::swap(v._start, _start);
        std::swap(v._end_of_storage, _end_of_storage);
        std::swap(v._end, _end);
    }

    void clear()
    {
        _end = _start;
    }

    void resize(int n, const T& val)
    {
        if(n < size())
        {
            _end = _start + n;
        }
        else
        {
            reserve(n);
            while(_start + n != _end)
            {
                *_end = val;
                _end++;
            }
        }
    }

    void reserve(int n)
    {
        if(n > capacity())
        {
            int old_size = size();
            T* tmp = new T[n];
            for(int i = 0; i < size(); i++)
            {
                tmp[i] = _start[i];
            }
            delete[] _start;
            _start = tmp;
            _end = _start + old_size;
            _end_of_storage = _start + n;
        }
    }

    void push_back(const T& val)
    {
        if(_end != _end_of_storage)
        {
            *_end = val;
            _end++;
        }
        else
        {
            reserve(capacity() == 0 ? 4 : 2 * capacity());
            *_end = val;
            _end++;
        }
    }

    int capacity()
    {
        return _end_of_storage - _start;
    }

    int size()
    {
        return _end - _start;
    }

    T& operator[](int pos)
    {
        assert(pos < size());
        return _start[pos];
    }

    const T& operator[](int pos) const
    {
        assert(pos < size());
        return _start[pos];
    }

    void pop_back()
    {
        if(!empty())
        {
            _end--;
        }
    }

    bool empty()
    {
        return _end == _start;
    }

    iterator begin()
    {
        return _start;
    }

    iterator end()
    {
        return _end;
    }

    const_iterator begin() const
    {
        return _start;
    }

    const_iterator end() const
    {
        return _end;
    }

    ~vector()
    {
        if(_start != nullptr)
        {
            delete[] _start;
            _start = _end = _end_of_storage = nullptr;
        }
    }
private:
    iterator _start = nullptr;
    iterator _end = nullptr;
    iterator _end_of_storage = nullptr;
    int _capacity = _end - _start;
};

template<class T>
void Print(vector<T>& v)
{
    vector<int>::iterator it = v.begin();
    for(; it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    Print<int>(v);
    std::cout << "---" << std::endl;

    vector<int> vv(v);
    Print<int>(vv);
    std::cout << "---" << std::endl;

    vector<int> v1(v.begin() + 1, v.end() - 1);
    Print<int>(v1);
    std::cout << "---" << std::endl;

    vector<int> v2(10, 1);
    Print<int>(v2);
    std::cout << "---" << std::endl;

    v2.insert(v2.begin() + 1, 9);
    Print<int>(v2);
    v2.erase(v2.begin() + 1);
    Print<int>(v2);
    std::cout << "---" << std::endl;

    vector<int> v3;
    v3 = v2;
    Print<int>(v3);
    std::cout << "---" << std::endl;

    v3.swap(v);
    Print<int>(v3);
    std::cout << "---" << std::endl;

    v3.resize(5, 0);
    Print<int>(v3);
    v3.resize(10, 9);
    Print<int>(v3);
    v3.pop_back();
    Print<int>(v3);
    // std::cout << v2.size() << " " << v2.capacity() << std::endl;
    // std::cout << "---" << std::endl;
    return 0;
}
