#include <iostream>
#include <stddef.h>

#define __cpluscplus

void func(int* a)
{
    printf("void func(int* a)\n");
}

void func(int a)
{
    printf("void func(int a)\n");
}

int main()
{
    // func(NULL);
    func(nullptr);
    return 0;
}
