#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    close(1);
    int fd = open("log.txt", O_RDWR | O_CREAT);
    char buffer[50] = "hello world";
    write(fd, buffer, sizeof(buffer));
    return 0;
}
