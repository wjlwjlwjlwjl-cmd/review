#include <iostream>
int main()
{
    int a = 10;
    // int& c;//引用必须在定义时初始化
    int &b = a;
    int &c = a; //一个对象可以有多个引用
    a = 20;
    std::cout << a << std::endl;
    printf("%p ", &a);
    printf("%p ", &b);

    //const引用
    int x = 3;
    const int& y = x * 3; 
    const int& z = x;
    const int& m = 10;

    return 0;
}
