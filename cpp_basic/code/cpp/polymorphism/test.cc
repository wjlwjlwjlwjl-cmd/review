#include <iostream>
using namespace std;

class A
{
public:
    virtual void func(int val = 1){ std::cout << "a->" << val << std::endl;}  
    void test(){ func();}
};

class B: public A
{
public:
    void func(int val = 2){ std::cout  << "b->" << val << std::endl;}
};

int main()
{
    B b;
    b.test();
    return 0;
}
