#include <iostream>
#include <vector>

void shell_sort(std::vector<int>& v)
{
    int n = v.size();
    int gap = n;
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
                    v[end + gap] = v[end];
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
    std::vector<int> v = {3, 8, 1, 5, 4, 0, 6, 2};
    shell_sort(v);
    for(auto& e: v)
    {
        std::cout << e << std::endl;
    }
    return 0;
}
