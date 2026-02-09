#include "comm.h"

int main()
{
    int shm_id = getShm(4096);
    char* shmaddr = (char*)shmat(shm_id, NULL, 0);
    sleep(5);
    int i = 0;
    while(i < 26)
    {
        *(shmaddr + i) = 'a' + i;
        i++;
        shmaddr[i] = 0;
        sleep(1);
    }
    shmdt(shmaddr);
    sleep(2);
    return 0;
}
