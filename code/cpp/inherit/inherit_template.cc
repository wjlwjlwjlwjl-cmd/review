#include <iostream>
#include <vector>
using namespace std;

template<class T>
class stack: public vector<T>
{
public:  
    void push(T val)
    {
        vector<T>::push_back(val);
    }
    void pop()
    {
        vector<T>::pop_back();
    }
    T top()
    {
        return vector<T>::back();
    }
private:
    vector<T> con;
};

int main()
{
    stack<int> st;
    st.push(1);
    st.push(2);
    st.pop();
    std::cout << st.top() << std::endl;
    return 0;
}
