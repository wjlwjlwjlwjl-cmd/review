#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
using namespace std;

typedef void(*func_t)();

vector<func_t> funcs;

void func1()
{
    cout << "running mission 1" << endl;
}

void func2()
{
    cout << "running mission 2" << endl;
}

void Load()
{
    funcs.push_back(func1);
    funcs.push_back(func2);
}

void Run()
{
    for(auto e: funcs)
    {
        e();
    }
    funcs.clear();
}

int main()
{
    pid_t pid = 0;
    if((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    if(pid == 0)
    {
        sleep(10);
        cout << "child exit..." << endl;
    }
    else
    {
        while(1)
        {
            
            int status;
            int ret = waitpid(pid, &status, WNOHANG);
            if(ret == 0)
            {
                cout << "child sleeping..." << endl;
                Load();
                Run();
                sleep(1);
            }
            else
            {
                if(WIFEXITED(status))
                {
                    stringstream ss;
                    ss << "child exit code ";
                    ss << WEXITSTATUS(status) << "\n";
                    cout << ss.str() << endl;
                    exit(0);
                }
                else
                {
                    cout << "wait fail" << endl;
                    fflush(stdout);
                    exit(1);
                }
            }
        }
    }
    return 0;
}
