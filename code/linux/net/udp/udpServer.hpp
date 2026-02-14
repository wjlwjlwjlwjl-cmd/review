#include "Logger.hpp"
#include "InetAddr.hpp"
#include "noCopy.hpp"

#include <string>

const uint16_t defaultport = 8080;
const uint16_t defaultsocket = -1;
const int defaultbuffersize = 1024;

class udpServer: public noCopy
{
public:  
    udpServer(int port = defaultport)
        : _port(port)
        , _socket(defaultsocket)
    {}

    void Init()
    {
        _socket = socket(AF_INET, SOCK_DGRAM, 0);
        if(_socket < 0)
        {
            ERROR("create socket fail");
            exit(1);
        }

        sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(_port);
        local.sin_family = AF_INET;

        int n = bind(_socket, (struct sockaddr*)&local, sizeof(local));
        if(n < 0)
        {
            ERROR("{} bind fail", _socket);
            exit(1);
        }
    }

    void Start()
    {
        char buffer[defaultbuffersize];
        while(1)
        {
            sockaddr_in src_addr;
            socklen_t len = sizeof(src_addr);
            memset(&src_addr, 0, len);

            int n = recvfrom(_socket, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&src_addr, &len);
            buffer[n] = 0;
            if(n > 0)
            {
                std::string starter = "this is a message handled by the server: "; 
                std::string message = starter + buffer;
                message[message.size()] = 0;
                InetAddr inetaddr((struct sockaddr*)&src_addr);
                inetaddr.PrintLog();
                DEBUG("message from client {}", buffer);
                n = sendto(_socket, message.c_str(), message.size(), 0, (struct sockaddr*)&src_addr, len);
                if(n < 0)
                {
                    ERROR("send to client fail{}", inetaddr.ip());
                    exit(1);
                }
            }
        }
    }
private:
    uint16_t _port;
    int _socket;
};
                    
