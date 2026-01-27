#include <stack>

using namespace std;

//fulfill a queue by stack
// 4  
// 3 2
class MyQueue {
public:
    MyQueue() {
        
    }
    
    void push(int x) {
        pushst.push(x);
    }
    
    int pop() {
        if(!popst.empty())
        {
            int ret = popst.top();
            popst.pop();
            return ret;
        }
        while(pushst.size() != 1)
        {
            popst.push(pushst.top());
            pushst.pop();
        }
        int ret = pushst.top();
        pushst.pop();
        return ret;
    }
    
    int peek() {
        if(!popst.empty())
        {
            return popst.top();
        }
        while(!pushst.empty())
        {
            popst.push(pushst.top());
            pushst.pop();
        }
        return popst.top();
    }
    
    bool empty() {
        return pushst.empty() && popst.empty();
    }
private:
    stack<int> pushst;
    stack<int> popst;
};
