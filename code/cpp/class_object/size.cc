#include <iostream>

class A
{
public:
    void f()
    {
        
    }
private:
    char _ch;
    // int _a;
};

struct B
{
public:
    void f1()
    {
        
    }

    void f2()
    {
        
    }

    void f3()
    {}
};

int main()
{
    A a;
    std::cout << sizeof(a) << std::endl;
    B b;
    std::cout << sizeof(b) << std::endl;
    return 0;
}
