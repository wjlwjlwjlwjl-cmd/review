#include <iostream>
using namespace std;

template<class T>
void func(T&& val)
{
    std::cout << val << std::endl;
}

int main()
{
    int&& rref = 1;
    const int n = 1;
    const int& lref = n;
    int a = 10;
    func(move(a));
    func(n);
    func(0);
    return 0;
}
