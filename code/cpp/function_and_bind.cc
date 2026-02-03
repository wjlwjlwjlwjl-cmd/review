#include <iostream>
#include <functional>

using namespace std;

class Plus
{
public:  
    int add(int x, int y)
    {
        return x + y;
    }
private:

};

int main()
{
    //使得调用成员函数时不必总传递this指针
    function<int(int, int)> f1 = bind(&Plus::add, Plus(), placeholders::_1, placeholders::_2);
    cout << f1(1, 1) << endl;
    return 0;
}
