class A
{
public:  
    void func()
    {}
    int _no;
};
class B: public A
{
public:
    void func(int a)
    {}
    char* _no;
};
int main()
{
    B b;
    b.func(1);
    b.A::func();
    b._no;
    return 0;  
}
