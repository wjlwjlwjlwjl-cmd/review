#include <iostream>

//时间复杂度是n^1.3，是对插入排序的优化，当gap == 1时，就是插入排序
void shell_sort(int* arr, int sz)
{
    int gap = sz;
    while(gap > 1)
    {
        gap = gap / 3 + 1;
        for(int i = 0; i < sz - gap; i++)
        {
            int end = i;            
            int tmp = arr[end + gap];
            while(end >= 0)
            {
                if(arr[end] > tmp)
                {
                    arr[end + gap] = arr[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            arr[end + gap] = tmp;
        }
    }
}

int main()
{
    int arr[] = {4, 9, 7, 1, 5, 2, 6};
    shell_sort(arr, sizeof(arr) / sizeof(int));
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
