#include <iostream>
#include <future>

std::string task(std::string str){
    std::cout << str << std::endl;
    return str + "handled";
}

int main(){
    std::future fut1 = std::async(std::launch::async, task, "thread-1");
    std::future fut2 = std::async(std::launch::deferred, task, "thread-2");
    auto ret = fut1.wait_for(std::chrono::seconds(1));
    if(ret == std::future_status::timeout){
        std::cout << "thread1 timeout" << std::endl;
    }
    auto ret2 = fut2.get();
    std::cout << ret2 << std::endl;
    return 0;
}