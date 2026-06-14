#include <iostream>
using namespace std;

class Base
{
public:  
    virtual void func() final
    {
        
    }
private:
};

class Derive: public Base
{
public:  
    // void func()
    // {
        
    // }
private:

};

int main()
{
    return 0;
}
