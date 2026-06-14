#include <stdio.h>
#include <assert.h>

//the area of the des and src in the memory can not overlap; since the copying is from the 
//front to back;
void* memcpy(void* des, const void* src, int num)
{
    void* ret = des;
    while(num--)
    {
        *(char*)des = *(char*)src;
        des = (char*)des + 1;
        src = (char*)src + 1;
    }
    return ret;
}

//the area of the pair can overlap, since this functions do it from the back to the front
void* memmove(void* des, const void* src, int num)
{
    void* ret = des;
    if(des <= src || (char*)des >= (char*)src + num)
    {
        while(num--)
        {
            *((char*)des) = *((char*)src);
            des = (char*)des + 1;
            src = (char*)src + 1;
        }
    }
    else
    {
        des = (char*)des + num - 1;
        src = (char*)src + num - 1;
        while(num--)
        {
            *((char*)des) = *((char*)src);
            des = (char*)des - 1;
            src = (char*)src - 1;
        }
    }
    
    return ret;
}

int main()
{
    int a[] = {1,2,3,4};
    int b[] = {0};
    memmove((void*)(a + 2), (void*)a, sizeof(a));
    for(int i = 0; i < sizeof(a)/sizeof(int); i++)
    {
        printf("%d ", (a + 2)[i]);
    }
    return 0;
}
