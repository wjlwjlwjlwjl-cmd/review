#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    std::string ip = "172.19.200.3";
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int n = bind(sock, (struct sockaddr*)&addr, len);
    if(n < 0)
    {
        perror("bind");
        exit(1);
    }

    n = listen(sock, 5);
    if(n < 0)
    {
        perror("listen");
        exit(1);
    }
    while(1)
    {
        char buff[1024 * 10] = {0};
        int client = accept(sock, nullptr, nullptr);
        int n = read(client, buff, sizeof(buff));
        if(n < 0)
        {
            perror("read");
            exit(1);
        }
        fprintf(stdout, "[request]: %s", buff);
        char buf[1024 * 10];
        std::string message = "hello world";
        n = sprintf(buf, "HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s", message.size(), message.c_str());
        n = write(client, buf, sizeof(buf));
    }

    return 0;
}