#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <type_traits>
#include <future>

class thread_pool{
public:
    thread_pool(int size = 5)
        : _stop(false)
    {
        _workers.resize(size);
        for(int i = 0; i < size; i++){
            auto task = std::function<void()>(
                [&](){
                    while(1){
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> ul(_mtx);
                            _cv.wait(ul, [&](){ return _stop || !_tasks.empty(); });
                            if(_stop && _tasks.empty()){
                                break;
                            }
                            task = std::move(_tasks.front());
                            _tasks.pop();
                        }
                        if(_stop && _tasks.empty()){
                            break;
                        }
                        task();
                        {
                            std::lock_guard<std::mutex> lg(_mtx);
                            std::cout << "run a task..." << std::endl;
                        }
                    }
                }
            );
            _workers[i] = std::thread(task);
        }
    }

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args){
        using return_type = std::invoke_result_t<F, Args...>;
        auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args...>(args...)));
        auto fut = task->get_future();
        {
            std::unique_lock<std::mutex> ul(_mtx);
            _tasks.push([=](){ (*task)(); });
        }
        _cv.notify_one();
        return fut;
    }

    ~thread_pool(){
        {
            std::lock_guard<std::mutex> lg(_mtx);
            _stop = true;
        }
        _cv.notify_all();
        for(auto& e: _workers){
            e.join();
        }
    }
private:
    std::mutex _mtx;
    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> _tasks;
    std::condition_variable _cv;
    bool _stop;
    int _size;
};

std::string test_func(std::string str){
    std::cout << str << std::endl;
    return str + " done";
}

int main(){
    thread_pool tp;
    auto fut = tp.enqueue(test_func, "task1");
    std::cout << fut.get() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}

