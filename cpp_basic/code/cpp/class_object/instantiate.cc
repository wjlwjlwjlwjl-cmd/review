#include <iostream>

class A
{
public:
    void f1()
    {
        std::cout << "f1" << std::endl;
    }
    void f2()
    {
        std::cout << "f2" << std::endl;
        std::cout << _a << std::endl;
    }
private:
    int _a;
};

int main()
{
    A *a = nullptr;
    a->f1();
    a->f2();
    return 0;
}
