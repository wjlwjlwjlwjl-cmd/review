#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* active(void* arg)
{
    string name = static_cast<const char*>(arg);
    while(1)
    {
        pthread_mutex_lock(&mutex);
        cout << "//" << name << "取得锁" << endl;
        pthread_cond_wait(&cond, &mutex); //在条件变量没有满足的时候，即使取得了锁，也要先交出锁进行等待，让其他线程先尝试执行
        cout << "//" << name << "actived" << endl;
        pthread_mutex_unlock(&mutex);
        cout << "//" << name << "释放锁" << endl;
    }
}

int main()
{
    pthread_t p1, p2;
    pthread_create(&p1, NULL, active, (void*)"thread-1");
    pthread_create(&p2, NULL, active, (void*)"thread-2");

    sleep(2);
    while(1)
    {
        pthread_cond_broadcast(&cond);  //两个为一组打印
        // pthread_cond_signal(&cond);  //一个一个打印
        sleep(1);
    }
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    return 0;
}
//thread-1取得锁
//thread-2取得锁
//thread-1actived
//thread-1释放锁
//thread-1取得锁
//thread-2actived
//thread-2释放锁
//thread-2取得锁
//thread-1actived
//thread-1释放锁
//thread-1取得锁
//thread-2actived
//thread-2释放锁
//thread-2取得锁
//thread-1actived
//thread-1释放锁
//thread-2actived
