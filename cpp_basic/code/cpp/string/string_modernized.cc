#include <assert.h>
#include <iostream>
#include <string.h>

class string
{
public:    
    string()
    {
        _str = nullptr;
    }

    string(const char* str)
    {
        std::cout << "普通构造" << std::endl;
        _str = new char[strlen(str) + 1];
        strcpy(_str, str);
    }

    string(const string& s)
        : _str(nullptr)
    {
        std::cout << "拷贝构造" << std::endl;
        string tmp(s._str);
        std::swap(_str, tmp._str);
    }

    string& operator=(string s)
    {
        std::cout << "赋值运算符重载" << std::endl;
        std::swap(s._str, _str);
        return *this;
    }

    ~string()
    {
        if(_str)
        {
            delete[] _str;
            _str = nullptr;
        }
    }
private:
    char* _str;
};

int main()
{
    string s1("hello world");
    string s2(s1);
    string s3;
    s3 = s1;
    return 0;
}
