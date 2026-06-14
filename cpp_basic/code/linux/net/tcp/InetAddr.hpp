#include <sys/types.h>
#include <sys/socket.h>
#include <stdint.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream>

#define CONV(in) (sockaddr*)&in

class InetAddr
{
public:  
    InetAddr(struct sockaddr* addr)
    {
        _addr = (struct sockaddr_in*)addr;
        _server_ip = ntohl(_addr->sin_port);
        _port = ntohs(_addr->sin_port);
    }

    uint32_t ip()
    {
        return _server_ip;
    }

    uint16_t port()
    {
        return _port;
    }

    void PrintLog()
    {
        std::stringstream ss;
        ss << "[" << _server_ip << ": " << _port << "]>>>";
        std::cout << ss.str() << std::endl;
    }
private:
    uint32_t _server_ip;
    uint16_t _port;
    sockaddr_in* _addr;
};
