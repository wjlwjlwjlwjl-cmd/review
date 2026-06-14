#include <stdio.h>

int cmp(void* p1, void* p2)
{
    return (*((int*)p1) - *((int*)p2));
}

void _swap(void* p1, void* p2, int sz)
{
    for(int i = 0; i < sz; i++)
    {
        char tmp = *((char*)p1 + i);
        *((char*)p1 + i) = *((char*)p2 + i);
        *((char*)p2 + i) = tmp;
    }
}

void qsort(void* base, int count, int sz, int(*cmp)(void*, void*))
{
    for(int i = 0; i < count - 1; i++)
    {
        for(int j = 0; j < count - i - 1; j++)
        {
            if(cmp((char*)base + j * sz, (char*)base + (j + 1)* sz) > 0)
            {
                _swap((char*)base + j * sz, (char*)base + (j + 1) * sz, sz);
            }
        }
    }
}

int main()
{
    int arr[] = {3, 9, 8, 5, 1};
    qsort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0]), cmp);
    for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
