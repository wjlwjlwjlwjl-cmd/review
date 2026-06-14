#include <atomic>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

class Node{
public:
    Node(int data)
        : data(data)
        , next(nullptr)
    {}
    int data;
    Node* next;
};

std::atomic<Node*> list_head;

void push_front(int data){
    Node* old_head = list_head.load();
    Node* new_head = new Node(data);
    while(1){
        new_head->next = old_head;
        if(list_head.compare_exchange_weak(old_head, new_head)){
            break;
        }
    }
}

int main(){
    std::vector<std::thread> threads(10);
    for(int i = 0; i < 10; i++){
        threads[i] = std::thread(push_front, i);
    }
    std::this_thread::sleep_for(1s);
    Node* node = list_head.load();
    while(node != nullptr){
        std::cout << node->data << " ";
        node = node->next;
    }
    for(int i = 0; i < 10; i++){
        threads[i].join();
    }
    return 0;
}

