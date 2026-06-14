#include <iostream>
#include "list.hpp"
int main()
{
    list<int> lt;
    for(int i = 0; i < 5; i++)
    {
        lt.push_back(i);
    }
    lt.insert(0, 100);
    lt.insert(1, 100);
    lt.insert(100, 100);
    for(list<int>::iterator it = lt.begin(); it != lt.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    list<int> lt1(lt);
    for(auto e: lt1)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;

    list<int> l2({1, 2, 3});
    list<int> l3 = {4, 5, 6};
    l2.erase(l2.begin() + 1);
    for(auto e: l2)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    for(auto e: l3)
    {
        std::cout << e << " ";
    }
    return 0;
}
