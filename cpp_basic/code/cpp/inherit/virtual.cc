#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
    string _name;
};
class Teacher:virtual public Person
{
public:
    int _emp;
};
class Student:virtual public Person
{
public:
    int _no;
};
class assistant: public Teacher, public Student
{
public:
    int _major_course;
};

int main()
{
    assistant a;
    a._name;
    return 0;
}
