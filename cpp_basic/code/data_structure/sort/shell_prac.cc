#include <iostream>
#include <vector>

void shell_sort(std::vector<int>& v)
{
    int n = v.size();
    int gap = v.size();
    while(gap > 1)
    {
        gap = gap / 3 + 1;
        for(int i = 0; i < n - gap; i += gap)
        {
            int end = i;
            int tmp = v[end + gap];
            while(end >= 0)
            {
                if(tmp < v[end])
                {
                    std::swap(v[end], v[end + gap]);
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            v[end + gap] = tmp;
        }
    }
}

int main()
{
    std::vector<int> v = {4, 9, 7, 1, 0, 5, 2};
    shell_sort(v);
    for(auto& e: v)
    {
        std::cout << e << " "; 
    }
    return 0;
}
