#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int infd = open("bridge", O_RDONLY);
    char buff[1024];    
    while(1)
    {
        int n = read(infd, buff, 1024);
        if(n == 0)
        {
            break;
        }
        else
        {
            std::cout << "server message: " << buff << std::endl; 
        }
    }
}
