#include <iostream>
#include <vector>

std::vector<int> tmp;

void merge_sort(std::vector<int>& v, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }
    int midi = (begin + end) / 2;
    merge_sort(v, begin, midi);
    merge_sort(v, midi + 1, end);
    tmp.resize(end - begin + 1);

    int left = begin, right = midi + 1;
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
        v[begin + i] = tmp[i];
    }
}

int main()
{
    std::vector<int> v = {4, 9, 2, 0, 6, 7, 1, 8};
    merge_sort(v, 0,  v.size() - 1);
    for(auto& e: v)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
