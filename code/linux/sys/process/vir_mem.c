#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int g_val= 0;

int main()
{
    pid_t pid = fork();
    if(pid == 0)
    {
        sleep(3);
        printf("child: %d %p", g_val, &g_val);
    }
    else
    {
        g_val = 100;
        printf("parent: %d %p", g_val, &g_val);
    }
    return 0;
}
