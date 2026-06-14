#include <stdio.h>

#define PRINT(n) printf("the val of "#n" is %d\n", n)
#define MAC_FUNC(type) type type##_max(type a, type b){ return a > b ? a : b; }

MAC_FUNC(int)

int main()
{
    int a = 10;
    PRINT(a);
    printf("%d\n", int_max(1, 2));
    return 0;
}
