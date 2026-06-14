#include <iostream>

void insert_sort(int* arr, int sz)
{
    for(int i = 0; i < sz - 1; i++)
    {
        int end = i;
        int tmp = arr[end + 1];
        while(end >= 0)
        {
            if(arr[end] > tmp)
            {
                arr[end + 1] = arr[end];
                end--;
            }
            else
            {
                break;
            }
        }
        arr[end + 1] = tmp;
    }
}

int main()
{
    int arr[] = {8, 3, 9, 5, 2, 1, 7, 6};
    insert_sort(arr, sizeof(arr) / sizeof(int));
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
