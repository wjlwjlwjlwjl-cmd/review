#include "process_pool.hpp"
int main()
{
    process_pool pp(10);
    pp.initPool();
    pp.dispatchTask();
    pp.destroyPool();
    return 0;
}
