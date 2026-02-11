#include <iostream>
#include <pthread.h>
#include <unistd.h>

void* func1(void*)
{
    std::cout << "thread1 running..." << std::endl;
    int *pa = (int*)malloc(sizeof(int));
    *pa = 10;
    return (void*)pa;
}

void* func2(void*)
{
    std::cout << "thread2 running..." << std::endl;
    int* pb = (int*)malloc(sizeof(int));
    *pb = 10;
    pthread_exit((void*)pb);
}

void* func3(void*)
{
    while(1)
    {
        std::cout << "thread3 running..." << std::endl;
    }
}

int main()
{
    pthread_t pid;
    void* ret;
    pthread_create(&pid, NULL, func1, NULL);
    pthread_join(pid, &ret);
    fprintf(stdout, "pthread1 exit, exit code is %d\n", *(int*)ret);
    free(ret);

    pthread_create(&pid, NULL, func2, NULL);
    pthread_join(pid, &ret);
    fprintf(stdout, "pthread2 exit, exit code is %d\n", *(int*)ret);
    free(ret);

    pthread_create(&pid, NULL, func3, NULL);
    pthread_cancel(pid);
    pthread_join(pid, &ret);
    fprintf(stdout, "thread3 exit, exit code is PTHREAD_CANCEL\n");
    return 0;
}
