#include <stack>
#include <queue>

using namespace std;

class MyStack {
public:
    MyStack() {
    }
    
    void push(int x) {
        if(q1.empty())
        {
            q2.push(x);
        }
        else
        {
            q1.push(x);
        }
    }
    
    int pop() {
        if(q1.empty())
        {
            while(q2.size() != 1)
            {
                q1.push(q2.front());
                q2.pop();
            }
            int ret = q2.front();
            q2.pop();
            return ret;
        }
        else
        {
            while(q1.size() != 1)
            {
                q2.push(q1.front());
                q1.pop();
            }
            int ret = q1.front();
            q1.pop();
            return ret;
        }
    }
    
    int top() {
        if(q1.empty())
        {
            return q2.back();
        }
        else
        {
            return q1.back();
        }
    }
    
    bool empty() {
        if(q1.empty())
        {
            return q2.empty();
        }
        else
        {
            return q1.empty();
        }
    }
private:
    queue<int> q1;
    queue<int> q2;
};
