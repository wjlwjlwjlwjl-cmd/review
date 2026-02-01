#include <deque>
#include <iostream>
using namespace std;

template<class T, class Con = deque<T>>
class queue
{
public:  
    queue()
    {}

    void push(const T& val = T())
    {
        _c.push_back(val);
    }

    void pop()
    {
        _c.pop_front();
    }

    T& front()
    {
        return _c.front();
    }

    T& back()
    {
        return _c.back();
    }

    size_t size()
    {
        return _c.size();
    }

    bool empty()
    {
        return _c.empty();
    }
private:
    Con _c;
};

int main()
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    std::cout << q.back() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;
    return 0;
}
