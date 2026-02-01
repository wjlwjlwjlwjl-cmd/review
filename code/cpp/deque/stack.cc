#include <deque>
#include <iostream>

using namespace std;

template<class T, class Con = deque<T>>
class stack
{
public:  
    stack(){}

    void push(const T& val)
    {
        _c.push_back(val);
    }

    void pop()
    {
        _c.pop_back();
    }

    T& top()
    {
        return _c.back();
    }

    int size()
    {
        return _c.size();
    }

    bool emtty()
    {
        return _c.empty();
    }
private:
    Con _c;
};

int main()
{
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    std::cout << st.top() << std::endl;
    return 0;
}
