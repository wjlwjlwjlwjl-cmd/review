#include <iostream>

//缺省参数必须在函数声明必须从右向左给
int add(int x, int y = 2, int z = 1)
{
   return x + y + z;
}

//函数的缺省值必须在声明时给定,不能在定义时在确定缺省值
int sub(int x, int y = 1, int z = 2);

int sub(int x, int y, int z)
{
   return x - y - z;
}

int main()
{
   //给予缺省参数时必须从左向右给予
   std::cout << add(1) << std::endl;
   std::cout << add(1, 9) << std::endl;
   std::cout << add(1, 9, 199) << std::endl;

   std::cout << sub(1) << std::endl;
   return 0;
}
