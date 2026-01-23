#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
    {
        perror("fork");
        return 1;
    }
    if(pid == 0)
    {
        printf("child sleeping...\n");
        sleep(5);
        printf("child exit\n");
    }
    else
    {
        int status;
        int ret = waitpid(-1, &status, 0); //blocked wait
        printf("wait end\n");
        if(ret <= 0)
        {
            perror("waitpid");
            return 1;
        }
        else
        {
            if(WIFEXITED(status))
            {
                printf("wait successfully, %d\n ", WEXITSTATUS(status));
            }
            else
            {
                printf("wait fail\n");
            }
        }
    }
    return 0;
}
