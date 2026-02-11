#include "mythread.hpp"

int main()
{
    MyThread mt([](){std::cout << "mission running" << std::endl;});
    mt.Start();
    mt.Join();
    return 0;
}
