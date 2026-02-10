#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    // pid_t pid;
    // pid = fork();
    // if(pid == 0)
    // {
    //     int a = 10;
    //     a /= 0;
    // }
    // int status;
    // waitpid(pid, &status, 0);
    // printf("exit signal: %d, core dump: %d", status & 0x7f, (status >> 7) & 1);
    while(1)
    {
        printf("1");
    }
    return 0;
}
