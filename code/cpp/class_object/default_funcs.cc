#include <iostream>

class A
{
public:    
    A() = default;
    A(A& a, int n = 10)
    {
        this->_a = n;
        std::cout << "拷贝构造" << std::endl;
    }
    ~A()
    {
        std::cout << _a << std::endl;
    }
    int _a;
};

class Date
{
public:
    Date(int year = 0, int month = 0, int day = 0)
    {
        a1._a = 1;
        a2._a = 2;
    }
    A getA()
    {
        std::cout << "传值返回" << std::endl;
        return a1;
    }
private:
    int _year;
    int _month;
    int _day;
    A a1;
    A a2;
};

int main()
{
    Date d;
    A a3;
    a3._a = 9;
    A a4(a3);
    std::cout << a4._a << std::endl;
    d.getA();
    return 0;
}
