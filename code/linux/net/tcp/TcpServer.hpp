#include "InetAddr.hpp" 
#include "Logger.hpp"
#include <string>
#include <cstring>

const int default_port = 8080;
const int default_socket = -1;
const int default_buffer_size = 1024;

class TcpServer
{
public:  
    TcpServer(int port = default_port)
        : _port(default_port)
        , _socket(default_socket)
    {}

    void Init()
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if(_socket < 0)
        {
            ERROR("create socket fail");
        }
        DEBUG("create socket success");
        int opt;
        int n = setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        if(n != 0)
        {
            ERROR("set reused addr and port fail");
            exit(1);
        }

        sockaddr_in listensock;
        memset(&listensock, 0, sizeof(listensock));
        listensock.sin_addr.s_addr = htonl(INADDR_ANY);
        listensock.sin_family = AF_INET;
        listensock.sin_port = htons(_port);

        if((bind(_socket, CONV(listensock), sizeof(listensock))) != 0)
        {
            ERROR("bind fail {}", _socket);
            exit(1);
        }
        DEBUG("bind success");

        if((listen(_socket, 5)) != 0)
        {
            ERROR("listen fail {}");
            exit(1);
        }
        DEBUG("exit success");
    }

    void Start()
    {
        DEBUG("server running...");
        while(1)
        {
            sockaddr_in cli_addr;
            memset(&cli_addr, 0, sizeof(cli_addr));
            socklen_t len;
            int client = accept(_socket, CONV(cli_addr), &len);
            if(client < 0)
            {
                DEBUG("ACCEPT ERROR");
                continue;
            }
            std::cout << "accept success" << std::endl;
            if(client > 0)
            {
                Service(client);
                close(client);
            }
        }
    }

    void Service(int client)
    {
        char buff[default_buffer_size];
        while(1)
        {
            int n = read(client, buff, sizeof(buff) - 1);
            if(n > 0)
            {
                buff[n] = 0;
                std::string echo = "recv from client## ";
                echo += buff; 
                std::cout << echo << std::endl;
                std::string resp = "server echo$$ ";
                resp += buff;
                n = write(client, resp.c_str(), strlen(resp.c_str()));
            }
            if(n == 0)
            {
                DEBUG("client exit");
                break;
            }
            if(n < 0)
            {
                ERROR("echo fail");
                exit(1);
            }
        }
    }
private:
    uint16_t _port;
    int _socket;
};
