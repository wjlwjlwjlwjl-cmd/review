#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

int main()
{
    int infd = open("fifo", O_RDONLY);
    char buf[1024];
    int n = 0;
    n = read(infd, buf, sizeof(buf));
    write(1, buf, n);
    fflush(stdout);
    close(infd);
    unlink("fifo");
    return 0;
}
