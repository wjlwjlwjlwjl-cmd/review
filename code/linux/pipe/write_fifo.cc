#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main()
{
    int infd = open("channel.hpp", O_RDONLY);
    if(infd == -1)
    {
        perror("infd");
        return 1;
    }
    int fifo = mkfifo("fifo", 0644);
    int outfd = open("fifo", O_WRONLY);
    int n = 0;
    char buf[1024];
    n = read(infd, buf, sizeof(buf));
    write(outfd, buf, n);
    close(infd);
    close(outfd);
    return 0;
}
