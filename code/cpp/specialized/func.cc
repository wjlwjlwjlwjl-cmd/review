#include <iostream>

class grade
{
public:  
    grade(int total)
        : _total(total)
    {}

    bool operator<(const grade& d)
    {
        return _total < d._total;
    }
private:
    int _total;
};

template <class T>
bool compare(T val1= T(), T val2 = T())
{
    return val1 < val2;
}

template<>
bool compare<grade*>(grade* g1, grade* g2)
{
    return *g1 < *g2;
}

int main()
{
    return 0;
}
