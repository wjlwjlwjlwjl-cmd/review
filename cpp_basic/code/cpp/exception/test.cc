#include <iostream>
#include <string>
using namespace std;

int Devide(int x, int y)
{
    try
    {
        if(y == 0)
        {
            string errmsg = "devide by zero";
            throw errmsg;
        }
        else
        {
            return (double)x / (double)y;
        }
    }
    catch(int errid)
    {
        cout << errid << endl;
    }
}

void Func()
{
    try
    {
        Devide(1, 0);
    }
    catch(const char* errmsg)
    {
        cout << 1;
        cout << errmsg << endl;
    }
    cout << __FUNCTION__ << ":" << __LINE__ << endl;
}

int main()
{
    try
    {
        Func();
    }
    catch(const string& errmsg)
    {
        cout << 2;
        cout << errmsg << endl;
    }
    return 0;
}
