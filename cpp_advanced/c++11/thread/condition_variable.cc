#include <condition_variable>
#include <thread>
#include <iostream>
#include <mutex>

static std::condition_variable cv;
static std::mutex mtx;
bool flag = true;

void func_thread0(int cnt){
    std::unique_lock<std::mutex> ul(mtx);
    for(int i = 0; i < cnt; i += 2){
        if(flag == false){
            cv.wait(ul);
        }
        std::cout << i << std::endl;
        flag = false;
        cv.notify_one();
    }
}

void func_thread1(int cnt){
    std::unique_lock<std::mutex> ul(mtx);
    for(int i = 1; i < cnt; i += 2){
        if(flag == true){
            cv.wait(ul);
        }
        std::cout << i << std::endl;
        flag = true;
        cv.notify_one();
    }
}


int main(){
    std::thread t0(func_thread0, 100);
    std::thread t1(func_thread1, 100);
    t0.join();
    t1.join();
    return 0;
}
