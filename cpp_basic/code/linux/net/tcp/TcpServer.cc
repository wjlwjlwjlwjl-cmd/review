#include "TcpServer.hpp"

int main()
{
    init_logger();
    TcpServer ts;
    ts.Init();
    ts.Start();
    return 0;
}
