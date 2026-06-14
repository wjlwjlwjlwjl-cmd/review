#include <iostream>
using namespace std;

void Print()
{
    cout << endl;
}

template<class T, class...Args>
void Print(T&& t, Args... args)
{
    cout << t << " ";
    Print(args...);
}

template<class...Args>
void Function(Args...args)
{
    Print(args...);
}

int main()
{
    Function(1, "wangjiale", 1.1);
    return 0;
}
