#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    int ret = fork();
    if(ret < 0)
    {
        perror("fork");
        return 1;
    }
    if(ret == 0)
    {
        printf("i'm a child %d", getpid());
    }
    else
    {
        printf("i'm the father %d", getpid());
    }
    return 0;
}
