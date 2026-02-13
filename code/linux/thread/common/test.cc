#include "ThreadPoolPractice.hpp"

using task_t = function<void()>;

void task1()
{
    cout << "task 1 done" << endl;
}

void task2()
{
    cout << "task 2 done" << endl;
}
void task3()
{
    cout << "task 3 done" << endl;
}
void task4()
{
    cout << "task 4 done" << endl;
}
void task5()
{
    cout << "task 5 done" << endl;
}
void task6()
{
    cout << "task 6 done" << endl;
}


int main()
{
    init_logger();

    ThreadPool<task_t> tp(3);
    tp.Init();
    tp.Start();

    tp.Enqueue(task1);
    tp.Enqueue(task2);
    tp.Enqueue(task3);
    tp.Enqueue(task4);
    tp.Enqueue(task5);
    tp.Enqueue(task6);

    sleep(3);

    tp.Stop();
    tp.Wait();
    return 0;
}
