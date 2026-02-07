#include <unistd.h>
#include <fcntl.h>
#include <iostream>
int main()
{
    close(1);
    int fd = open("log.txt", O_APPEND|O_RDWR);
    dup2(fd, 1);
    char buffer[10] = "wjl";
    write(1, buffer, sizeof(buffer));
    return 0;
}
