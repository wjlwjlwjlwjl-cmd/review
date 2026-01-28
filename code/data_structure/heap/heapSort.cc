#include <stdlib.h>
#include <iostream>
#include <stdio.h>

void AdjustDown(int* data, int parent, int n)
{
    int child = parent * 2 + 1;
    while(child < n)
    {
        if(child + 1 < n && data[child + 1] < data[child])
        {
            child++;
        }
        if(data[child] < data[parent])
        {
            std::swap(data[child], data[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
        else
        {
            break;
        }
    }
}

void AdjustUp(int* data, int child)
{
    int parent = (child - 1) / 2;
    while(parent >= 0)
    {
        if(data[parent] < data[child])
        {
            std::swap(data[parent], data[child]);
            child = parent;
            parent = (child - 1) / 2;
        }
        else
        {
            break;
        }
    }
}

void heap_sort(int* arr, int sz)
{
    for(int i = (sz - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(arr, i, sz);
    }
    for(int i = sz - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        AdjustDown(arr, 0, sz);
    }
}

int main()
{
    int arr[] = {3, 9, 7, 8, 5, 1};
    heap_sort(arr, sizeof(arr) / sizeof(int));
    for(int i = 0; i < 6; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
