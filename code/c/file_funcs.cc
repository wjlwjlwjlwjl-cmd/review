#include <stdio.h>
int main()
{
    FILE* pf = fopen("log.txt", "w");
    fputs("hello world", pf);
    fclose(pf);
    return 0;
}
