#include <iostream>

class A
{
public:    
    // explicit A(int a)
    A(int a)
        : _a(a)
    {}
    A(int a, int aa)
        : _a(a)
        , _aa(aa)
    {}

    int getA() const
    {
        return _aa;
    }
private:
    int _a;
    int _aa;
};

class B
{
public:
    B(const int& b)
        : b(b)
    {}
    B(const A& a)
        : b(a.getA())
    {}
private:
    int b;
};

int main()
{
    A a1 = 1;
    A a2 = {2, 2};
    B b1(a2);
    B b2(10);
    return 0;
}
