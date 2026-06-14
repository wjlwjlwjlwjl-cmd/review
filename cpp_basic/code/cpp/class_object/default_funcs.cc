#include <iostream>

class A
{
public:    
    A()
    {}

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
    friend bool operator==(const Date& d1, const Date& d2);
    friend void operator++(Date&, int);
    friend std::istream& operator>>(std::istream& in, Date& d);
    Date(int year = 0, int month = 0, int day = 0)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    void operator++()
    {
        _day += 1;
    }

    Date& operator=(const Date& d)
    {
        if(this != &d)      
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;
    }

    int getDay() const 
    {
        return _day;
    }

private:
    int _year;
    int _month;
    int _day;
    A _a;
};
std::istream& operator>>(std::istream& in, Date& d)
{
    std::cout << "please input one number" << std::endl;        
    in >> d._day;
    return in;
}

bool operator==(const Date& d1, const Date& d2)
{
    return d1._year == d2._year &&
    d2._month == d1._month && 
    d1._day == d2._day;
}

void operator++(Date& d, int)
{
    d._day++;
}

std::ostream& operator<<(std::ostream& out, const Date& d)
{
    std::cout << d.getDay() << std::endl;
    return out;
}

int main()
{
    // Date d;
    // A a3;
    // a3._a = 9;
    // A a4(a3);
    // std::cout << a4._a << std::endl;
    // d.getA();
    Date d1;
    Date d2;
    d1++;
    ++d2;
    if(d1 == d2 && operator==(d1, d2))
    {
        std::cout << "d1 and d2 is eqail" << std::endl;
    }
    d1++;
    Date d3;
    d3 = d2 = d1;
    std::cout << d3.getDay() << std::endl;
    std::cout << d2.getDay() << std::endl;
    std::cout << d1.getDay() << std::endl;
    std::cout << d1 << d2 << d3 << std::endl;
    std::cin >> d1;
    std::cout << "--" << d1 << std::endl;
    return 0;
}
