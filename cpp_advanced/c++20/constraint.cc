#include <iostream>
#include <concepts>
#include <vector>

using namespace std;

template <class T>
concept C1 = requires{
    typename T::iterator; //访问嵌套类型必须加typename关键字，用以区分类型定义和类型访问
};

template <class T>
concept C2 = requires(T a, T b){
    a + b;
};

void range(C1 auto& con){
    for(auto e: con){
        std::cout << e << std::endl;
    }
}

int main(){
    int arr[10];
    std::vector<int> v({1, 2, 3});
    range(v);
    return 0;
}