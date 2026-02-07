#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main()
{
    close(0);
    int fd = open("fd.cc", O_RDONLY);
    cout << fd << endl;
    char buffer[1];
    while(0 != read(fd, buffer, sizeof(buffer)))
    {
        cout << buffer;
    }
    close(fd);
    return 0;
}
