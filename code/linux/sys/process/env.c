#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[], char* env[])
{
    //for(int i = 0; env[i]; i++)
    //{
    //    printf("%s ", env[i]);
    //}
    //printf("\n");
    //extern char** environ;
    //for(int i = 0; env[i]; i++)
    //{
    //    printf("%s ", environ[0]);
    //}
    
    char* my_env = getenv("PATH");
    printf("%s\n", my_env);
    return 0;
}
