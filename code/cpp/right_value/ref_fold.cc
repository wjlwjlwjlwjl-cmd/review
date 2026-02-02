#include <iostream>
using namespace std;

void func(int&& val)
{
    std::cout << val << std::endl;
}

int main()
{
    int&& rref = 1;
    int n = 1;
    int& lref = n;
    func(n);
    func(0);
    return 0;
}
