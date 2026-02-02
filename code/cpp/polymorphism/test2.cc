#include <iostream>
using namespace std;

class A
{
public:
    virtual void func()
    {
        std::cout << "a::func" << std::endl;
    }
};

class B: public A
{
private:
    virtual void func()
    {
        std::cout << "b::func" << std::endl;
    }
};

int main()
{
    A* pa = (A*)new B;
    pa->func();
    return 0;
}
