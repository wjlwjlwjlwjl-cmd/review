#include <iostream>
#include <vector>
using namespace std;

void count_sort(vector<int>& v)
{
    int max = v[0], min = v[0];
    for(auto e: v)
    {
        if(e > max)
        {
            max = e;
        }
        if(e < min)
        {
            min = e;
        }
    }
    int range = max - min + 1;
    int* count = (int*)calloc(range, sizeof(int));

    for(auto e: v)
    {
        count[e - min]++;
    }

    int j = 0;
    for(int i = 0; i < range; i++)
    {
        while(count[i]--)
        {
            v[j++] = i + min;
        }
    }

    free(count);
}

int main()
{
    vector<int> v = {5, 9, 3, 8, 7, 1, 2, 4, 0, 6};
    count_sort(v);
    for(auto e: v)
    {
        std::cout << e << " ";
    }
    return 0;
}
