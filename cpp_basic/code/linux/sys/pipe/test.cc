#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>

int main()
{
    char buff[100];
    int pipe_fd[2];
    int ret = pipe(pipe_fd);
    if(ret != 0)
    {
        perror("make pipe");
        return 1;
    }

    while(fgets(buff, 100, stdin))
    {
        int len = strlen(buff);
        write(pipe_fd[1], buff, len);
        memset(buff, 0, sizeof(buff));
        read(pipe_fd[0], buff, sizeof(buff));
        write(1, buff, len);
    }
    return 0;
}
