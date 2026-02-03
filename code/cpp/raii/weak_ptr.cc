#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main()
{
    string* pstr = new string("wangjiale");
    shared_ptr<string> sp(pstr);
    shared_ptr<string> sp1(sp);
    weak_ptr<string> wp = sp;
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;
    cout << "---" << endl;

    sp = make_shared<string>("wang");
    sp1 = make_shared<string>("jiale");
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;
    cout << "---" << endl;

    wp = sp1;
    cout << wp.expired() << endl;
    cout << wp.use_count() << endl;
    cout << "---" << endl;

    auto sp2 = wp.lock();
    *sp2 += "~";
    cout << *sp2 << endl;

    return 0;
}
