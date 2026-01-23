#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("the pid is %d", getpid());
    printf("the pid is %d", getppid());
    return 0;
}
