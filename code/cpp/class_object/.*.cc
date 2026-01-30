#include <iostream>
class A
{
public:    
    void func()
    {
        std::cout << "triggered by .*" << std::endl;
    }
private:
};

typedef void(A::*PF)();

int main()
{
    A a;
    PF pf = &A::func;
    (a.*pf)();
    return 0;
}
