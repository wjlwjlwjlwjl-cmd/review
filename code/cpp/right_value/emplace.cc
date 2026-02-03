#include <iostream>
#include <list>

using namespace std;

class Date
{
public:
    friend ostream& operator<<(ostream& out, Date& d);
    Date(int year, int month)
        : _year(year)
        , _month(month)
    {}

private:
    int _year;
    int _month;
};

ostream& operator<<(ostream& out, Date& d)
{
    out << d._year << " " << d._month << " ";
    return out;
}

int main()
{
    list<Date> lt;
    Date d1(1, 1);
    lt.emplace_back(d1);
    lt.emplace_back(2, 2);
    for(auto e: lt)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
