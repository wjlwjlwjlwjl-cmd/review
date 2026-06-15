#include <iostream>
#include <future>
#include <thread>

void task(std::shared_future<std::string> sf){
    std::cout << "get data: " << sf.get() << std::endl;
}

int main(){
    std::thread threads[4];
    std::promise<std::string> prom;
    std::shared_future<std::string> sf = prom.get_future().share();
    for(int i = 0; i < 4; i++){
        threads[i] = std::thread(task, sf);
    }
    prom.set_value("hello world");
    for(int i = 0; i < 4; i++){
        threads[i].join();
    }
    return 0;
}