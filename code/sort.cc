#include <iostream>

//move the largest(smallest) elements to the end of the array(the part that has not been ordered)
void bubble_sort(int* arr, int sz)
{
    int flag = 0;
    for(int i = 0; i < sz - 1; i++)
    {
        for(int j = 0; j < sz - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
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
    int arr[10] = {9, 4, 3, 8, 1, 2, 0, 5, 6, 7};
    int sz = sizeof(arr)/sizeof(int);
    bubble_sort(arr, sz);
    for(int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
