#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 1;
    }
    if(pid == 0)
    {
        printf("child: running...\n");
        sleep(5);
        printf("child: done\n");
    }
    else
    {
        printf("parent:sleeping..\n");
        sleep(10);
    }
    return 0;
}
