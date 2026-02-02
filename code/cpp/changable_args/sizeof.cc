#include <iostream>
using namespace std;

template<class...Args>
void Print(Args...args)
{
    cout << sizeof...(args) << endl;
}

int main()
{
    double x = 1.0;
    Print(1, "wangjiale");
    Print(x);
    return 0;
}
