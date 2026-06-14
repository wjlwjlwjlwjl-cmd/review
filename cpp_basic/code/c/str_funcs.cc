#include <iostream>
#include <cstring>
#include <assert.h>

int strlen(char* str)
{
    if(str == nullptr)
    {
        return 0;
    }
    char* begin = str;
    while(*str != '\0')
    {
        str++;
    }
    return str - begin;
}

char* strcpy(const char* src, char* des)
{
    if(src == nullptr || des == nullptr)
    {
        return des;
    }
    char* ret = des;
    while((*des++ = *src++))
    {}
    return ret;
}

char* strcat(char* des, const char* src)
{
    assert(des != nullptr && src != nullptr);
    char* ret = des;
    while(*des)
    {
        des++;
    }
    while((*des++ = *src++))
    {}
    return ret;
}

int strcmp(const char* str1, const char* str2)
{
    assert(str1 != NULL && str2 != NULL);
    while(*str1 == *str2)
    {
        if(*str1 == '\0')
        {
            return 0;
        }
        str1++; str2++;
    }
    return *str1 - *str2;
}

//the first appearance of str2 in str1
char* mystrstr(const char* str1, const char* str2)
{
    char* cp = (char*)str1;
    char* s1, *s2;

    if(!str2)
    {
        return NULL;
    }

    while(*cp)
    {
        s1 = cp;
        s2 = (char*)str2;
        while(*s1 && *s2 && *s1 == *s2)
        {
            s1++; s2++;
        }
        if(!*s2)
        {
            return cp;
        }
        cp++;
    }
    return NULL;
}

int main()
{
    char str1[] = "hello world";
    char str2[] = "world";
    //std::cout << strlen(str) << std::endl;
    
    //char* des;
    //std::cout << strcpy(str1, des) << std::endl;

    //char* ret = strcat(str2, str1);
    //printf("%s\n", ret);
    
    //std::cout << strcmp(str1, str2) << std::endl;
    //std::cout << ('a' - '\0') << std::endl;
    
    // std::cout << strstr(str1, str2) << std::endl;
    std::cout << strtok(str1, str2) << std::endl;
    return 0;
}
