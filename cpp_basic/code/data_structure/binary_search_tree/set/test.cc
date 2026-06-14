#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
    set<int> s;
    for(int i = 0; i < 10; i++)
    {
        s.insert(i);
    }
    auto tar = s.find(5);
    s.erase(tar);
    for(auto e: s)
    {
        cout << e << " ";
    }

    initializer_list<string> lt = {"w", "a"};
    set<string> ss(lt);
    string tar1 = "w";
    if(find(ss.begin(), ss.end(), tar1) != ss.end())
    {
        cout << "find" << " w" << endl;
    }

    auto upper = s.upper_bound(9);
    auto lower = s.lower_bound(6);
    s.erase(lower, upper);
    for(auto e: s)
    {
        cout << e << " ";
    }
    return 0;
}
