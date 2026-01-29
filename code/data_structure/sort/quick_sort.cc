#include <iostream>
#include <stack>
using namespace std;

//hoare版本
void quick_sort(int *arr, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    int key = begin;
    int left = begin, right = end;
    while(left < right)
    {
        while(left < right && arr[right] >= arr[key])
        {
            right--;
        }
        while(left < right && arr[left] <= arr[key])
        {
            left++;
        }
        std::swap(arr[left], arr[right]);
    }

    std::swap(arr[left], arr[key]);
    key = left;
    quick_sort(arr, begin, key - 1);
    quick_sort(arr, key + 1, end);
}

//双指针版本
void quick_sort_double_ptr(int* arr, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    int key = begin;
    int prev = begin, cur = begin;
    while(cur <= end)
    {
        if(arr[cur] < arr[key])
        {
            std::swap(arr[++prev], arr[cur]);
        }
        cur++;
    }
    std::swap(arr[key], arr[prev]);
    key = prev;
    quick_sort_double_ptr(arr, begin, key - 1);
    quick_sort_double_ptr(arr, key + 1, end);
}

//优化版本，加三数取中（也可以随机选择key，降低数据有序的影响）和小区间优化（避免递归过深）
void insert_sort(int* arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int end = i;
        int tmp = arr[i + 1];
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

int getMidi(int* arr, int begin, int end)
{
    int midi = (begin + end) / 2;
    if(arr[begin] < arr[end])
    {
        if(arr[midi] < arr[begin])
        {
            return begin;
        }
        if(arr[midi] > arr[end])
        {
            return end;
        }
        else
        {
            return midi;
        }
    }
    else
    {
        if(arr[end] > arr[midi])
        {
            return end;
        }
        else if(arr[begin] < arr[midi])
        {
            return begin;
        }
        else
        {
            return midi;
        }
    }
}

void quick_sort_refined(int* arr, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    if(end - begin + 1 < 10)
    {
        insert_sort(arr, end - begin + 1);
    }
    else
    {
    int midi = getMidi(arr, begin, end);
    std::swap(arr[begin], arr[midi]);

    int key = begin;
    int left = begin, right = end;
    while(left < right)
    {
        while(left < right && arr[right] >= arr[key])
        {
            right--;
        }
        while(left < right && arr[left] <= arr[key])
        {
            left++;
        }
        std::swap(arr[left], arr[right]);
    }

    std::swap(arr[left], arr[key]);
    key = left;
    quick_sort(arr, begin, key - 1);
    quick_sort(arr, key + 1, end);
    }
}

//不用递归，通过栈实现快速排序
void quick_sort_non_recursive(int* arr, int begin, int end)
{
    stack<int> st;
    st.push(end);
    st.push(begin);
    
    while(!st.empty())
    {
        int begin = st.top();
        st.pop();
        int end = st.top();
        st.pop();
        if(begin >= end)
        {
            continue;
        }
        int key = begin;
        int left = begin, right = end;
        while(left < right)
        {
            while(left < right && arr[right] >= arr[key])
            {
                right--;
            }
            while(left < right && arr[left] <= arr[key])
            {
                left++;
            }
            std::swap(arr[left], arr[right]);
        }

        std::swap(arr[left], arr[key]);
        key = left;
        st.push(end);
        st.push(key + 1);
        st.push(key - 1);
        st.push(begin);
    }
}

int main()
{
    int arr[] = {9, 5, 0, 6, 3, 1, 4, 2, 8, 7};
    int n = sizeof(arr) / sizeof(int);
    quick_sort_non_recursive(arr, 0, n - 1);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
