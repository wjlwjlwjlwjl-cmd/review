#include <sys/select.h>
#include <unistd.h>
#include <iostream>

int main()
{
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(0, &fs);
    while(1)
    {
        std::cout << ">" << std::endl;
        int n = select(1, &fs, nullptr, nullptr, nullptr);
        if(n < 0)
        {
            perror("select");
            exit(1);
        }
        if(FD_ISSET(0, &fs))
        {
            char buff[1024] = {0};
            read(0, buff, sizeof(buff));
            fprintf(stdout, "input## %s", buff);
        }
        FD_ZERO(&fs);
        FD_SET(0, &fs);
    }
    return 0;
}