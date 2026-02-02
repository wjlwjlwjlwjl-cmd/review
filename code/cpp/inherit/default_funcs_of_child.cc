#include <iostream>
#include <string>
using namespace std;

class Person
{
public:  
    string name;
    int age;
    Person(string name, int age)
        : name(name)
        , age(age)
    {}

    Person(const Person& p)
        : name(p.name)
        , age(p.age)
    {}

    Person& operator=(const Person& p)
    {
        name = p.name; age = p.age;
        return *this;
    }

    ~Person()
    {
        std::cout << "基类析构函数" << std::endl;
    }
};

class Student: public Person
{
public:  
    int _no;
    Student(string name, int age, int no)
        : Person(name, age)
        , _no(no)
    {}

    Student(const Student& stu)
        : Person(stu)
        , _no(stu._no)
    {}

    Student operator=(const Student& stu)
    {
        Person::operator=(stu);
        _no = stu._no;
        return *this;
    }
    ~Student()
    {
        std::cout << "派生类析构函数" << std::endl;
    }
};

int main()
{
    Student stu("wang", 1, 1);
    return 0;
}
