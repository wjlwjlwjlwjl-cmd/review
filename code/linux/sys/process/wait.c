#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    int pid;
    if((pid = fork()) < 0)
    {
        perror("fork");
        return 1;
    }
    if(pid == 0)
    {
        printf("child sleeping\n");
        sleep(3);
        printf("child exited\n");
    }
    else
    {
        int status;
        /*
         *check the process whether or not exit normally, using WIFEXITED(status)
         *check the status of the exited process, using WEXITEDSTATUS(status)
        */
        int pid = wait(&status);
        if(pid <= 0)
        {
            perror("wait");
            return 1;
        }
        if((status & 0x7F) == 0)
        {
            printf("the child exit normally, the exit status is %d\n", (status >> 8) & 0xFF);
        }
        else
        {
            printf("the child exit abnormally, the exit signal is %d\n", status & 0x7F);
        }
    }
    return 0;
}
