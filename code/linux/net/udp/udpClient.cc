#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <gflags/gflags.h>
#include <string.h>

#include "Logger.hpp"

DEFINE_string(server_ip, "127.0.0.1", "server's ip");

int main(int argc, char* argv[])
{
    init_logger();
    google::ParseCommandLineFlags(&argc, &argv, true);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        ERROR("sock create fail");
        exit(1);
    }
    DEBUG("sock create success");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = inet_addr(FLAGS_server_ip.c_str());
    addr.sin_port = htons(8080);
    addr.sin_family = AF_INET;
    socklen_t len = sizeof(addr);

    while(1)
    {
        std::cout << "Please Enter# ";
        std::string buff;
        std::getline(std::cin, buff);

        int n = sendto(sock, buff.c_str(), buff.size(), 0, (sockaddr*)&addr, len);
        if(n < 0)
        {
            ERROR("send fail");
            exit(1);
        }
        DEBUG("send success");

        char resp[1024];
        n = recvfrom(sock, resp, sizeof(resp) - 1, 0, (sockaddr*)&addr, &len);
        resp[n] = 0;
        if(n < 0)
        {
            ERROR("recv fail");
            exit(1);
        }
        DEBUG("recv success");
        std::cout << resp << std::endl;
    }
    return 0;
}
