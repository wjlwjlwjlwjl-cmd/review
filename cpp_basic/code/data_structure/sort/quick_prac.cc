#include <iostream>
#include <vector>

void quick_sort(std::vector<int>& v, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }
    int key = begin;
    int left = begin, right = end;
    while(left < right)
    {
        while(left < right && v[right] >= v[key])
        {
            right--;
        }
        while(left < right && v[left] <= v[key])
        {
            left++;
        }
        std::swap(v[left], v[right]);
    }
    std::swap(v[key], v[left]);
    key = left;
    quick_sort(v, begin, key - 1);
    quick_sort(v, key + 1, end);
}

int main()
{
    std::vector<int> v = {3, 9, 4, 1, 0, 6 ,5, 8};
    quick_sort(v, 0, v.size() - 1);

    for(auto& e: v)
    {
        std::cout << e << " ";
    }
    return 0;
}
