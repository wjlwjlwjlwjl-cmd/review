#include <ranges>
#include <iostream>

int main(){
    //惰性求值，非拥有，链式调用
    auto fibnacci = std::views::iota(0)
        | std::views::transform(
            [=](int x){
                static int a = 0, b = 1;
                int next = a + b;
                a = b;
                b = next;
                return a;
            }
        );
    auto ret = fibnacci | std::views::take(10);
    for(auto e: ret){
        std::cout << e << " ";
    }
    std::cout << std::endl;
    return 0;
}