#include <cstdio>
int add(int x, int y)
{
    return x+y;
}

int sub(int x, int y)
{
    return x - y;
}

int div(int x, int y)
{
    if(y == 0)
    {
        printf("division with zero not allowed\n");
    }
    return x/y;
}

int mul(int x, int y)
{
    return x * y;
}

int main()
{
next:
    printf("please choose one from the list below\n");
    printf("0: exit | 1: add | 2: sub | 3: div | 4: mul\n");
    int option;
    scanf("%d", &option);
    if(option == 0)
    {
        return 0;
    }
    int(*funcs[5])(int, int) = {0, add, sub, div, mul};
    int x,  y;
    printf("please input the number\n");
    scanf("%d %d", &x, &y);
    while(1)
    {
        switch(option)
        {
        case 0:
            break;
        case 1:
            printf("%d\n", funcs[option](x, y));
            break;
        case 2:
            printf("%d\n", funcs[option](x, y));
            break;
        case 3:
            printf("%d\n", funcs[option](x, y));
            break;
        case 4:
            printf("%d\n", funcs[option](x, y));
            break;
        default:
            printf("unknown method chosen");
            break;
        }
        goto next;
    }

    return 0;
}
