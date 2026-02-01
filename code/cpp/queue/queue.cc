#include <iostream>
#include <list>
class queue
{
public:  
    queue()
    {}

    void push(int val)
    {
        lt.push_back(val);
    }

    void pop()
    {
        lt.pop_front();
    }

    int front()
    {
        return lt.front();
    }

    int back()
    {
        return lt.back();
    }
private:
    std::list<int> lt;
};
