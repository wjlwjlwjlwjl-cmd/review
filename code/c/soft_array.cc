#include <stdio.h>
#include <stdlib.h>

struct A
{
    int a;
    int arr[];
};

int main()
{
    struct A* pa = (struct A*)calloc(1, sizeof(struct A) + sizeof(int)* 10);
    pa->a = 100;
    for(int i = 0; i < 10; i++)
    {
        printf("%d ", pa->arr[i]);
    }
    pa = (struct A*)realloc(pa, sizeof(struct A) + sizeof(int) * 100);
    printf("\n %d", sizeof(pa));
    free(pa);
    return 0;
}
