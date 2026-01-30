#include <iostream>

class A
{
public:    
    A(int a)
        : _a(a)
    {}

    class B
    {
    public:  
        B(int b)
            : _b(b)
        {}

        void Print(A& a)
        {
            std::cout << a._a << " " << _b << std::endl;
        }
    private:
        int _b;
    };
private:
    int _a;
};

int main()
{
    A a(1);
    A::B b(5);
    b.Print(a);
    return 0;
}
