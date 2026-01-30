#include <iostream>

class A
{
public:    
    friend class B;

    A(int a)
        : _a(a)
    {}

private:
    int _a;
};

class B
{
public:
    B(int b)
        : _b(b)
    {}

    void Print(A& a)
    {
        std::cout << _b << " " << a._a << std::endl;
    }
private:
    int _b;
};

int main()
{
    A a(1);
    B b(2);
    b.Print(a);
    return 0;
}
