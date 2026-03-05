#include <iostream>
#include <vector>

std::vector<int> tmp;

void merge_sort(std::vector<int>& v, int begin,  int end)
{
    if(begin >= end)
    {
        return;
    }

    int midi = (begin + end) / 2;
    merge_sort(v, begin, midi);
    merge_sort(v, midi + 1, end);

    int left = begin;
    int right = midi + 1;
    tmp.resize(end - begin + 1);
    int i = 0;
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
    for(int i = 0; i < tmp.size(); i++)
    {
        v[i + begin] = tmp[i];
    }
}

int main()
{
    std::vector<int> v = {3, 9, 8, 5, 1, 0, 2, 7};
    merge_sort(v, 0, v.size() - 1);
    for(auto& e: v)
    {
        std::cout << e << " "; 
    }
    return 0;
}
