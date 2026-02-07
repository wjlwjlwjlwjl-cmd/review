#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstring>

int main()
{
    const char* msg1 = "hello printf\n";
    const char* msg2 = "hello fwrite\n";
    const char* msg3 = "hello write\n";

    printf("%s", msg1);
    fwrite(msg2, strlen(msg2), 1, stdout);
    write(1, msg3, strlen(msg3));
    fork();
    return 0;
}
hello write
hello printf
hello fwrite
hello printf
hello fwrite
