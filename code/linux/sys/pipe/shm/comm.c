#include "comm.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int comm(int size, int shmflg)
{
    key_t key = ftok(PATHNAME, PROJ_ID);
    int shmid = shmget(key, size, shmflg);
    if(shmid < 0)
    {
        perror("shmget");
    }
    return shmid;
}

void destroy(int shm_id)
{
    shmctl(shm_id, IPC_RMID, NULL);
}

int createShm(int size)
{
    return comm(size, IPC_CREAT | IPC_EXCL | 0666);
}

int getShm(int size)
{
    return comm(size, IPC_CREAT);
}
