#include <iostream>
#include <string>

using namespace std;

class Person
{
public:  
    Person() = default;
    Person(const string& name, int age)
        : _name(name)
        , _age(age)
    {}

    Person(const Person& p)
        : _name(p._name)
        , _age(p._age)
    {}

    Person& operator=(const Person& p)
    {
        _name = p._name;
        _age = p._age;
        return *this;
    }

    ~Person()
    {
        
    }
private:
    string _name;
    int _age;
};

int main()
{
    Person p1("wangjiale", 19);
    Person p2 = move(p1);
    Person p3;
    p3 = move(p1);
    return 0;
}
