#include <iostream>
#include <string.h>
#include <assert.h>
//主要实现构造函数，拷贝构造，赋值运算符重载，析构函数

class string
{
public:
    friend std::ostream& operator<<(std::ostream& out, const string& s);
    string()
    {
        _str = nullptr;
    }

    string(const char* str)
        : _str(new char[strlen(str) + 1])
    {
        if(str == nullptr)
        {
            assert(false);
        }
        std::cout << "构造函数" << std::endl;
        strcpy(_str, str);
    }

    string(const string& s)
    {
        _str = new char[strlen(s._str) + 1];
        strcpy(_str, s._str);
        std::cout << "拷贝构造函数" << std::endl;
    }

    string& operator=(const string& s)
    {
        char* tmp = new char[strlen(s._str) + 1];
        delete[] _str;
        _str = tmp;
        strcpy(_str, s._str);
        std::cout << "赋值运算符重载" << std::endl;
        return *this;
    }

    string& operator+=(const char& c)
    {
        int length = strlen(_str);
        _str[length] = c;
        _str[length + 1] = '\0';
        return *this;
    }

    ~string()
    {
        std::cout << "析构函数" << std::endl;
        delete[] _str;
        _str = nullptr;
    }
private:
    char* _str;
};

std::ostream& operator<<(std::ostream& out, const string& s)
{
    std::cout << s._str << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, string& s)
{
    char ch = in.get();
    while(ch != '\n' && ch != ' ' && ch != '\0')
    {
        s += ch;
        ch = in.get();
    }
    return in;
}

int main()
{
    string s("hello world");
    string s1(s);
    string s2;
    s2 = s1;
    string s3("hello cpp");
    s2 = s3;
    std::cout << s << std::endl;
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cin >> s;
    std::cout << s << std::endl;
    return 0;
}
