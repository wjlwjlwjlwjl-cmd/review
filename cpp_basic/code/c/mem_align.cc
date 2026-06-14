#include <stdio.h>

struct Stu
{
    char* name;  
};

struct s
{
    int a: 3;
    char b: 4;
};

struct A
{
 int _a:2;
 int _b:5;
 int _c:10;
 int _d:30;
};

int  main()
{
    char name[] = "王家乐";
    Stu stu;
    stu.name = name;
    printf("the size of the struct is %d\n", sizeof(struct s));
    A a;
    int numa = 1;
    a._a = numa;
    return 0;
}
