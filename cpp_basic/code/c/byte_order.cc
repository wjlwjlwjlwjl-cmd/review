#include <stdio.h>
int main()
{
    int a = 1;
    int* pa = &a;
    if(*((char*)pa))
    {
        printf("small");
    }
    else
    {
        printf("big");
    }
    return 0;
}
