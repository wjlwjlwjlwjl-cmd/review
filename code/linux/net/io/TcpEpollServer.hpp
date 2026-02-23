#include <sys/epoll.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <functional>

typedef std::function<void(const std::string&, std::string& rsp)> work;

class Epoll
{
public:
    int Create()
    {
        _epoll_fd = epoll_create(10);
    }

    void Add(int sock)
    {
        struct epoll_event ev;
        ev.data.fd = sock;
        ev.events = EPOLLIN;
        int n = epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, sock, &ev);
        if(n < 0)
        {
            perror("epoll");
            exit(1);
        }
        fprintf(stdout, "add %d to epoll", sock);
    }

    void Del(int sock)
    {
        int n = epoll_ctl(_epoll_fd, EPOLL_CTL_DEL, sock, nullptr);
        if(n < 0)
        {
            perror("epoll_ctl");
            exit(1);
        }
        fprintf(stdout, "del %d from epoll", sock);
    }

    void Wait(std::vector<int>& carrier)
    {
        struct epoll_event evs[10];
        int n = epoll_wait(_epoll_fd, evs, sizeof(evs) / sizeof(struct epoll_event), -1);
        if(n < 0)
        {
            perror("epoll_wait");
            exit(1);
        }
        for(int i = 0; i < n; i++)
        {
            carrier.push_back(evs[i].data.fd);
        }
    }
private:
    int _epoll_fd;
};

class TcpEpollServer
{
public:
    TcpEpollServer(const std::string& ip, int port)
    {
        _epoll.Create();
        _listen_sock = socket(AF_INET, SOCK_STREAM, 0);
        if(_listen_sock < 0)
        {
            perror("socket");
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_family = AF_INET;
        addr.sin_port = port;

        int n = bind(_listen_sock, (struct sockaddr*)&addr, sizeof(addr));
        if(n < 0)
        {
            perror("bind");
            exit(1);
        }
        n = listen(_listen_sock, 10);
        if(n < 0)
        {
            perror("listen");
            exit(1);
        }
        _epoll.Add(_listen_sock);
    }

    void Start()
    {
        while(1)
        {
            std::vector<int> output;
            _epoll.Wait(output);
            for(auto& e: output)
            {
                if(e == _listen_sock)
                {
                    int newsock = e;
                    _epoll.Add(newsock);
                }
                else
                {
                    char buff[1024] = {0};
                    int n = read(e, buff, sizeof(buff));
                    if(n < 0)
                    {
                        _epoll.Del(e);
                        close(e);
                        perror("read");
                        exit(1);
                    }
                    std::string rsp;
                    std::string req = buff;
                    // work(req, rsp);
                    write(e, rsp.c_str(), rsp.size());
                }
            }
        }
    }
private:
    int _listen_sock;
    Epoll _epoll;
};