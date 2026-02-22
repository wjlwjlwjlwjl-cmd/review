#include <poll.h>
#include <iostream>
#include <unistd.h>

int main()
{
    struct pollfd fds; 
    fds.fd = 0;
    fds.events = POLLIN;
    while(1)
    {
        int n = poll(&fds, 1, 1000);
        if(n < 0)
        {
            perror("poll");
            exit(1);
        }
        if(n > 0)
        {
            char buffer[1024] = {0};
            int n = read(0, buffer, sizeof(buffer));
            if(n < 0)
            {
                perror("read");
                exit(1);
            }
            if(fds.revents == POLLIN)
            {
                fprintf(stdout, "%s", buffer);
            }
        }
    }
    return 0;
}