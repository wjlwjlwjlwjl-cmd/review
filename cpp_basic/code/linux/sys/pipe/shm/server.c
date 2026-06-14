#include "comm.h"

int main()
{
    int shm_id = createShm(4096);
    char* shmaddr = (char*)shmat(shm_id, NULL, 0);
    sleep(5);
    int i = 0;
    while(i++ < 26)
    {
        printf("%s\n", shmaddr);
        sleep(1);
    }
    shmdt(shmaddr);
    sleep(2);
    destroy(shm_id);
    return 0;
}
