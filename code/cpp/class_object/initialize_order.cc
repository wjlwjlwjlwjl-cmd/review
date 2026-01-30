#include <iostream>

class A
{
public:
    A(int a)
        : _a1(a)
        , _a2(_a1)
    {
        
    }

    void Print()
    {
        std::cout << _a1 << " " << _a2 << std::endl;
    }
private:
    int _a1 = 2;
    int _a2 = 2;
};

int main()
{
    A a(1);
    a.Print();
    return 0;
}
