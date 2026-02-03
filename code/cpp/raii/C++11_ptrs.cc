#include <iostream>
#include <memory>
using namespace std;

class Date
{
public:  
    Date() = default;
    Date(int year, int month, int day)
        : _year(year)
        , _month(month)
        , _day(day)
    {
        
    }
    int _year;
    int _month;
    int _day;
};

template<class T>
class DeleteArray
{
public:
    void operator()(T* ptr)  
    {
        delete[] ptr;
    }
};

template<class T>
void DeleteArrFunc(T* ptr)
{
    delete[] ptr;
}

int main()
{
    Date* pd1 = new Date(1, 1, 1);
    int* arr = new int[10];
    // auto_ptr<Date> ap1(pd1); //对auto_ptr进行拷贝构造，会导致原来的管理对象被悬空，这样再通过原来的管理对象访问时，就会导致崩溃
    // auto_ptr<Date> ap2(ap1);
    // ap1->_year++;

    unique_ptr<Date> up1(pd1);
    // unique_ptr<Date> up2(up1); //unique_ptr不支持拷贝构造，只允许移动构造
    unique_ptr<Date> up2(move(up1)); //因为unique_ptr只支持移动构造，所以这意味着一个资源的管理对象至多有一个
    unique_ptr<int[]> up3(arr);

    shared_ptr<Date> sp1 = make_shared<Date>(1, 1, 1);
    shared_ptr<Date> sp2(sp1);
    shared_ptr<Date> sp3((sp2));
    cout << sp1.use_count() << endl;

    int *arr1 = new int[10];
    unique_ptr<int, DeleteArray<int>> up4(arr1); //通过仿函数的方式制作删除器
    shared_ptr<int> sp4(arr1, DeleteArray<int>());

    unique_ptr<int, void(*)(int*)> up5(arr1, DeleteArrFunc<int>); //通过函数指针的方式定制删除器
    shared_ptr<int> sp5(arr1, DeleteArrFunc<int>);

    return 0;
}
