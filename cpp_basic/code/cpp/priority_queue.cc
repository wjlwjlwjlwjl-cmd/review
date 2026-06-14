#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <string>

using namespace std;

class exam_info
{
public:  
    string _name;
    int _total;
    bool operator<(const exam_info& ei) const
    {
        return _total < ei._total;
    }

    bool operator>(const exam_info& ei) const 
    {
        return _total > ei._total;
    }
};

int main()
{
    vector<int> v({1, 3, 9, 8, 6});
    priority_queue<int> heap;
    for(auto e: v)
    {
        heap.push(e);
    }
    std::cout << heap.top() << std::endl;

    //优先级队列默认使用vector作为底层容器
    priority_queue<int, vector<int>, greater<int>> vv(v.begin(), v.end());
    std::cout << vv.top() << std::endl;

    vector<exam_info> infos = {{"zhangsan", 100}, {"lisi", 99}, {"zhouliu", 98}};
    priority_queue<exam_info> heap2;
    for(auto e: infos)
    {
        heap2.push(e);
    }
    std::cout << heap2.top()._total << std::endl;

    return 0;
}
