#include <fcntl.h>
#include <iostream>
#include <unistd.h>

void SetNoBlock(int fd)
{
    int fl = fcntl(fd, F_GETFD);
    if(fl < 0)
    {
        perror("fcntl");
        exit(1);
    }
    fcntl(fd, F_SETFD, fl|O_NONBLOCK);
}

int main()
{
    SetNoBlock(0);
    while(1)
    {
        char buffer[1024] = {0};
        int read_size = read(0, buffer, sizeof(buffer));
        std::cout << 1 << std::endl;
        if(read_size < 0)
        {
            perror("read");
            exit(1);
        }
        fprintf(stdout, "input## %s", buffer);
    }
    return 0;
}