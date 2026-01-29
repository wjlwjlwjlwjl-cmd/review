#include <iostream>

void AdjustDown(int* arr, int parent, int n)
{
    int child = parent * 2 + 1;
    while(child < n)
    {
        if(child + 1 < n && arr[child + 1] > arr[child])
        {
            child++;
        }
        if(arr[parent] < arr[child])
        {
            std::swap(arr[parent], arr[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

//时间复杂度n*logn，想法就是对于堆顶元素，一定是最值，所以将它换到最后，再重新建堆，一次往复
void heap_sort(int* arr, int sz)
{
    //初始化堆
    for(int i = (sz - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(arr, i, sz);
    }
    //修正同层之间的大小关系
    for(int i = sz - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        AdjustDown(arr, 0, i);
    }
}

int main()
{
    int arr[] = {8, 5, 0, 4, 6, 1, 3, 2, 7, 9};
    int sz = sizeof(arr) / sizeof(int);
    heap_sort(arr, sz);
    for(int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
