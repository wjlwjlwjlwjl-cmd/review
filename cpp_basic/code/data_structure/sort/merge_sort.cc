#include <iostream>
#include <vector>
using namespace std;

vector<int> tmp;

void merge_sort(vector<int>& v, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    tmp.resize(end - begin + 1); // 注意这一部的调整大小的操作，对于tmp而言，不扩容肯能会产生在存放数据时的越界访问
    tmp.clear();
    int midi = (begin + end) / 2;

    merge_sort(v, begin, midi);
    merge_sort(v, midi + 1, end);

    int left = begin, right = midi + 1, i = 0;
    while(left <= midi && right <= end)
    {
        tmp[i++] = v[left] < v[right] ? v[left++] : v[right++];
    }
    while(left <= midi)
    {
        tmp[i++] = v[left++];
    }
    while(right <= end)
    {
        tmp[i++] = v[right++];
    }
    for(int i = begin; i <= end; i++)
    {
        v[i] = tmp[i - begin];
    }
}

int main()
{
    vector<int> v = {9, 4, 6, 1, 8, 0, 2, 5, 7, 3};
    merge_sort(v, 0, v.size() - 1);
    for(auto e: v)
    {
        std::cout << e << " ";
    }
    return 0;
}
