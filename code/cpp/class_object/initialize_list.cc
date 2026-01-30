#include <iostream>

class Date
{
public:
    friend std::ostream& operator<<(std::ostream& out, const Date& d);
    Date(int year, int month, int day)
        : _year(year)
        , _day(day)
        , _month(month)
    {
        _year = 1000;
        _day = 1000;
        _month = 1000;
    }
private:    
    int _year;
    int _day;
    int _month;
};

std::ostream& operator<<(std::ostream& out, const Date& d)
{
    std::cout << d._year << " " << d._month << " " << d._day << std::endl;
    return out;
}

int main()
{
    Date d(1, 1, 1);
    std::cout << d;
    return 0;
}
