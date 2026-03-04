#include <iostream>
#include <vector>

void adjustDown(std::vector<int>& v, int parent, int n)
{
    int child = parent * 2 + 1;
    while(child < n)
    {
        if(child + 1 < n && v[child + 1] > v[child])
        {
            child += 1;
        }
        if(v[parent] < v[child])
        {
            std::swap(v[parent], v[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void heap_sort(std::vector<int>& v)
{
    int n = v.size();
    for(int i = (n - 1 - 1) / 2; i >= 0; i--)
    {
        adjustDown(v, i, n);
    }
    int end = n - 1;
    while(end > 0)
    {
        std::swap(v[0], v[end]);
        adjustDown(v, 0, end);
        end--;
    }
}

int main()
{
    std::vector<int> v = {3, 8, 1, 2, 9, 5, 7, 0};
    heap_sort(v);
    for(auto& e: v)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
