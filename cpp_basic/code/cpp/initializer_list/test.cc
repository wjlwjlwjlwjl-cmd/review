#include <iostream>
#include <vector>
using namespace std;

class A
{
public:  
    A(int m = 1, int n = 1)
        : _m(m)
        , _n(n)
    {}
    A(const A& a)
        : _m(a._m)
        , _n(a._n)
    {}
private:
    int _m;
    int _n;
};

int main()
{
    A a({1, 2});
    A aa = {1, 2};
    A a2 = 1;

    initializer_list<int> il;
    il = {1, 2, 3, 4};
    vector<int>v(il);
    for(auto e: v)
    {
        cout << e << endl;
    }
    return 0;
}
