#include <iostream>
#include <vector>

void insert_sort(std::vector<int>& v)
{
    for(int i = 0; i < v.size() - 1; i++)
    {
        int end = i;
        int tmp = v[i + 1];
        while(end >= 0)
        {
            if(tmp < v[end])
            {
                std::swap(v[end], v[end + 1]);
                end--;
            }
            else
            {
                break;
            }
        }
        v[end + 1] = tmp;
    }
}

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
        std::swap(v[right], v[left]);
    }
    std::swap(v[key], v[left]);
    key = left;
    quick_sort(v, begin, key - 1);
    quick_sort(v, key + 1, end);
}

int main()
{
    std::vector<int> v = {4, 2, 8, 0, 5, 1, 6};
    insert_sort(v);
    for(auto e: v)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
