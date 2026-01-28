#include <iostream>
#include <vector>

void select_sort(std::vector<int>& arr)
{
    int begin = 0, end = arr.size() - 1;
    while(begin < end)
    {
        int max = begin, min = begin;
        for(int i = begin + 1; i <= end; i++) //这里因为我们设置max和min时都是默认begin，所以end要包含，否则不参与最值遍历
        {
            if(arr[max] < arr[i])
            {
                max = i;
            }
            if(arr[min] > arr[i])
            {
                min = i;
            }
        }
        std::swap(arr[begin], arr[min]);
        if(max == begin)
        {
            max = min;
        }
        std::swap(arr[end], arr[max]);
        begin++;
        end--;
    }
}

int main()
{
    std::vector<int> arr = {8, 7, 4, 9, 0, 2, 5, 1, 3, 6};
    select_sort(arr);
    for(auto e: arr)
    {
        std::cout << e << " ";
    }
}
