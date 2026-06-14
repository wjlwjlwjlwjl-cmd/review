#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main()
{
    const char* const env[] = {"PATH=/bin:/usr/bin", "TERM=console", NULL};
    char* const argv[] = {"..", NULL};
    //execl("/usr/games/sl", "", NULL);
    //execlp("clear", "", NULL);
    // if(execle("/usr/bin/pwd", "", NULL, env) == -1)
    // {
    //     cout << "execle faile" << endl;
    // }
    if(execvp("cd", argv) == -1)
    {
        cout << "rf" << endl;
    }
    return 0;
}
