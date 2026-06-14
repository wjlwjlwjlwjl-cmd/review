#include <iostream>

void bubble_sort(int* arr, int n)
{
    int flag = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j < n - i; j++)
        {
            if(arr[j - 1] > arr[j])
            {
                std::swap(arr[j - 1], arr[j]);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
}

int main()
{
    int arr[] = {8, 5, 9, 0, 4, 2, 7, 6, 3, 1};
    int n = sizeof(arr) / sizeof(int);
    bubble_sort(arr, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
