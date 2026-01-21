#include <iostream>

union byte_order
{
  char ch;
  int num;
};

int main()
{
  union byte_order bo;
  bo.ch = '1';
  if(bo.num)
  {
    std::cout << "当前机器为小端" << std::endl;
  }
  else
  {
    std::cout << "当前机器为大端" << std::endl;
  }
  return 0;
}
