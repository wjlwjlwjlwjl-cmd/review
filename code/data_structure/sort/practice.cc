#include <iostream>
#include <vector>
#include <stack>

void insert_sort(int* arr, int n)
{
    for(int i = 0; i < n - 1; i++)
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

void shell_sort(int* arr, int n)
{
    int gap = n;
    while(gap > 1)
    {
        gap = gap / 3;
        for(int i = 0; i < n - gap; i += gap)
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

void select_sort(int* arr, int n)
{
    int begin = 0, end = n - 1;
    while(begin < end)
    {
        int max = begin, min = begin;
        for(int i = begin + 1; i <= end; i++)
        {
            if(arr[max] < arr[i])
            {
                max = i;
            }
            if(arr[min] > arr[i])
            {
                min = i;
            }
        }
        std::swap(arr[begin], arr[min]);
        if(max == begin)
        {
            max = min;
        }
        std::swap(arr[end], arr[max]);
        begin++;
        end--;
    }
}

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

void heap_sort(int* arr, int n)
{
    for(int i = (n - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(arr, i, n);
    }

    int end = n - 1;
    while(end > 0)
    {
        std::swap(arr[0], arr[end]);
        AdjustDown(arr, 0, end);
        end--;
    }
}

int getMidi(int* arr, int begin, int end)
{
    int midi = (begin + end) / 2;
    if(arr[begin] < arr[end])
    {
        if(arr[midi] > arr[end])
        {
            return end;
        }
        else if(arr[midi] < arr[begin])
        {
            return begin;
        }
        else
        {
            return midi;
        }
    }
    else
    {
        if(arr[midi] < arr[end])
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

void quick_sort(int *arr, int begin, int end)
{
    //小区间优化，避免递归过深
    if(end - begin + 1 < 10)
    {
        insert_sort(arr, end - begin);
    }

    if(begin >= end)
    {
        return;
    }
    //三数取中
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

void quick_sort_no_recusion(int* arr, int begin, int end)
{
    std::stack<int> st;    

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

void bubble_sort(int *arr, int n)
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
            return;
        }
    }
}

std::vector<int> tmp;

void merge_sort(int* arr, int begin, int end)
{
    if(begin >= end)
    {
        return;
    }

    int midi = (begin + end) / 2;
    tmp.resize(end - begin + 1);
    tmp.clear();

    merge_sort(arr, begin, midi);
    merge_sort(arr, midi + 1, end);

    int left = begin;
    int right = midi + 1;
    int i = 0;
    while(left <= midi && right <= end)
    {
        tmp[i++] = arr[left] < arr[right] ? arr[left++] : arr[right++];
    }
    while(left <= midi)
    {
        tmp[i++] = arr[left++];
    }
    while(right <= end)
    {
        tmp[i++] = arr[right++];
    }

    for(int i = 0; i < end - begin + 1; i++)
    {
        arr[i + begin] = tmp[i];
    }
}

void count_sort(int* arr, int n)
{
    int max = 0;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    int* count = (int*)calloc(max + 1, sizeof(int));
    for(int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }
    int j = 0;
    for(int i = 0; i <= max; i++)
    {
        while(count[i]--)
        {
            arr[j++] = i;
        }
    }
}

int main()
{
    int arr[] = {8, 1, 4, 2, 3, 9, 7, 6, 0, 5};
    int n = sizeof(arr) / sizeof(int);
    // insert_sort(arr, n);
    //shell_sort(arr, n);
    // select_sort(arr, n);
    // heap_sort(arr, n);
    // quick_sort(arr, 0, n - 1);
    // quick_sort_double_ptr(arr, 0, n - 1);
    // quick_sort_no_recusion(arr, 0, n - 1);
    // bubble_sort(arr, n);
    // merge_sort(arr, 0, n - 1);
    count_sort(arr, n);
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
