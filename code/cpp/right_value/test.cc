#include <iostream>
int main()
{
    const int& lr1 = 1;
    int n = 1;
    int&& rr1 = std::move(n);
    return 0;
}
