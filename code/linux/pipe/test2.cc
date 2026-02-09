#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

#define ERR_EXIT(errmsg)\
do \
{\
    perror(errmsg);\
    exit(EXIT_FAILURE);\
}\
while(0)\

int main()
{
    int fds[2];
    if(pipe(fds) != 0)
    {
        ERR_EXIT("make pipe");
    }
    pid_t pid;
    if(fork() == 0)
    {
        close(fds[0]);
        char buff[100] = "hello";
        write(fds[1], buff, sizeof(buff));
        exit(EXIT_SUCCESS);
    }
    close(fds[1]);
    char buff[100];
    read(fds[0], buff, sizeof(buff));
    write(1, buff, sizeof(buff));
    return 0;
}
