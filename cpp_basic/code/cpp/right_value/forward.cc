#include <iostream>

void Func(int& val)
{
    std::cout << "左值引用" << std::endl;
}

void Func(int&& val)
{
    std::cout << "右值引用" << std::endl;
}

template<class T>
void Function(T&& val)
{
    // Func(val);
    Func(std::forward<T>(val));
}

int main()
{
    Function(1);
    int a = 0;
    Function(a);
    return 0;
}
