#include <stdio.h>

int atoi(char* str)
{
    int ret = 0;
    while(*str)
    {
        ret *= 10;
        ret += *str - '0';
        str++;
    }
    return ret;
}

int main()
{
    char number[] = "1";
    printf("%d\n", atoi(number));
    return 0;
}
