#include <iostream>
#include <string>
using namespace std;

class Person
{
public:  
    string _name;
    int age;
};

class Student: public Person
{
public:  
    int _no;
};

int main()
{
    Student stu;
    //派生类可以赋值给基类的指针和引用
    Person* pper = &stu;
    Person& rper = stu;
    std::cout << pper->_name << " " << rper.age << std::endl;
    return 0;
}
