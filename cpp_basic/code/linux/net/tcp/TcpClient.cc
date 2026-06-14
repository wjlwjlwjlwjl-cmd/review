#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <gflags/gflags.h>

#include "Logger.hpp"
#include "InetAddr.hpp"

DEFINE_string(server_ip, "127.0.0.1", "server's ip");

int main(int argc, char* argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
    init_logger();

    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(8080);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(FLAGS_server_ip.c_str());
    // inet_pton(AF_INET, FLAGS_server_ip.c_str(), &server.sin_addr);

    int n = connect(server_sock, CONV(server), sizeof(server));
    if(n < 0)
    {
        ERROR("connect fail");
        exit(1);
    }
    DEBUG("connect success");

    while(1)
    {
        std::cout << "Please input##";
        std::string buffer;
        std::cin.clear();
        std::getline(std::cin, buffer);
        int n = write(server_sock, buffer.c_str(), buffer.size());
        if(n > 0)
        {
            char buff[1024];
            int m = read(server_sock, buff, sizeof(buff) - 1);
            if(m > 0)
            {
                buff[m] = 0;
                std::cout << buff << std::endl;
            }
            else
            {
                DEBUG("read zero, exit");
                break;
            }
        }
        else
        {
            DEBUG("write zero, exit");
            break;
        }
    }
    return 0;
}
