#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("i am the parent\n");
        sleep(3);
        exit(0);
    }
    else
    {
        printf("i am the child\n");
        sleep(10);
    }
    return 0;
}
