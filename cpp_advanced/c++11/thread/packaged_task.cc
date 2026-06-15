#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <iostream>
#include <condition_variable>

void runner(std::queue<std::packaged_task<int()>>& taskq, std::condition_variable& cv, std::mutex& mtx){
    while(1){
        std::packaged_task<int()> task;
        {
            std::unique_lock<std::mutex> ul(mtx);
            cv.wait(ul, [&](){return !taskq.empty();});
            task = std::move(taskq.front());
            taskq.pop();
        }
        if(!task.valid()){
            break;
        }
        task();
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << "run a task..." << std::endl;
        }
    }
}

int main(){
    std::queue<std::packaged_task<int()>> taskq;
    std::condition_variable cv;
    std::mutex mtx;
    std::thread t(runner, std::ref(taskq), std::ref(cv), std::ref(mtx));
    for(int i = 0; i < 10; i++){
        std::packaged_task<int()> task([=](){
            std::cout << "run: " << i << std::endl;
            return i;
        });
        taskq.push(std::move(task));
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cv.notify_all();
    t.join();
    return 0;
}
