#include <iostream>

class A
{
public:    
    void Print()
    {
        std::cout << _a << " " << _aa << std::endl;
    }

    static void static_print()
    {
        std::cout << _aa << std::endl;
    }

private:
    int _a = 1;
    static int _aa;
};

int A::_aa = 1;

int main()
{
    A a;
    a.Print();
    a.static_print();
    return 0;
}
