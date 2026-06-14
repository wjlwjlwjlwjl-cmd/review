#include <thread>
#include <iostream>
#include <vector>

void Print(int val)
{
    std::cout << "print in thread: " << val << std::endl;   
}

int main()
{
    std::thread t1(Print, 10);
    std::vector<std::thread> threads(4);
    for(int i = 0; i < 4; i++)
    {
        threads[i] = std::thread(Print, i);
    }
    t1.join();
    for(int i = 0; i < 4; i++)
    {
        threads[i].join();
    }
    return 0;
}
