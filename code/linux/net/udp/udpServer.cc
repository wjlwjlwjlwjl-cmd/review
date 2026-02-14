#include "udpServer.hpp"

int main()
{
    init_logger();
    udpServer us;
    us.Init();
    us.Start();
    return 0;
}
