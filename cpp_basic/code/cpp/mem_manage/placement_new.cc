#include <iostream>
class A
{
public:
    A(int a = 0)
        : _a(a)
    {
        std::cout << "构造函数" << std::endl;
    }
    int getVal()
    {
        return _a;
    }
    ~A()
    {
        std::cout << "析构函数" << std::endl;
    }
private:
    int _a;
};

int main()
{
    A* pa1 = (A*)malloc(sizeof(A));
    new(pa1)A;
    std::cout << pa1->getVal() << std::endl;
    pa1->~A();
    operator delete(pa1);

    A* pa2 = (A*)malloc(sizeof(A));
    new(pa2)A(10);
    std::cout << pa2->getVal() << std::endl;
    pa2->~A();
    operator delete(pa2);
    return 0;
}
