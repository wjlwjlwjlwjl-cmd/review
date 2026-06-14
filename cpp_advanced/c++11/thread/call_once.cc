#include <mutex>
#include <string>
#include <thread>
#include <iostream>
#include <vector>

std::once_flag flag;

void set_winner(std::string& s){
    std::cout << "the winner is " << s << std::endl; 
}

void race(std::string name){
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::call_once(flag, set_winner, name);
}

int main(){
    std::vector<std::thread> threads(4);
    for(int i = 0; i < threads.size(); i++){
        threads[i] = std::thread(race, std::to_string(i));
    }
    for(int i = 0; i < threads.size(); i++){
        threads[i].join();
    }
    return 0;
}
