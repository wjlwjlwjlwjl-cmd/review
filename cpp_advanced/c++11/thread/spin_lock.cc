#include <atomic>
#include <iostream>
#include <thread>

static int cnt = 0;

class SpinLock{
public:
    SpinLock()
        : _flag(false)
    {}

    void lock(){
        while(_flag.exchange(true)){}
    }

    void unLock(){
        _flag.store(false);
    }
private:
    std::atomic<bool> _flag;
};

class SpinLock2{
public:
    SpinLock2()
        : _flag(ATOMIC_FLAG_INIT)
    {}

    void lock(){
        while(_flag.test_and_set()){}
    }

    void unLock(){
        _flag.clear();
    }
private:
    std::atomic_flag _flag;
};

static SpinLock2 sl;

void buy(){
    while(1){
        sl.lock();
        if(cnt < 100000){
            cnt++;
            std::cout << cnt << std::endl;
            sl.unLock();
        }
        else{
            std::cout << "sold out" << std::endl;
            sl.unLock();
            break;
        }
    }
}

int main()
{
    std::thread t1(buy);
    std::thread t2(buy);
    std::thread t3(buy);
    std::thread t4(buy);
    std::thread t5(buy);
    std::thread t6(buy);
    t1.join();
    t3.join();
    t2.join();
    t4.join();
    t5.join();
    t6.join();
    return 0;
}
