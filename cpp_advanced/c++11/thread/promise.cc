#include <exception>
#include <thread>
#include <iostream>
#include <future>

void producer(std::promise<std::string>& prom, std::string& data){
    try{
        if(data.empty()){
            throw std::logic_error("data is empty");
        }
        prom.set_value(data);
        std::cout << "produce data: " << data << std::endl;
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
        prom.set_exception(std::current_exception());
    }
}

void consumer(std::promise<std::string>& prom){
    try{
        std::future fut = prom.get_future();
        auto ret = fut.get();
        std::cout << "consume data: " << ret << std::endl;
    }
    catch(const std::exception& e){
        std::cout << e.what() << std::endl;
    }
}

int main(){
    std::string data("hello world");
    std::promise<std::string> prom;
    std::async(std::launch::async, producer, std::ref(prom), std::ref(data));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::async(std::launch::async, consumer, std::ref(prom));
    return 0;
}