#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

//server写，client读
int init()
{
    return mkfifo("bridge", 0644);
}

int main()
{
    int fifo = init();
    int outfd = open("bridge", O_WRONLY);
    char buff[1024];
    std::cout << "please input message" << std::endl;
    fgets(buff, sizeof(buff), stdin);
    write(outfd, buff, strlen(buff) + 1);
    return 0;
}
