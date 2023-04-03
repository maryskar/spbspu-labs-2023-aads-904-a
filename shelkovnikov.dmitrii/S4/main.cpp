#include <iostream>
#include <labList1.h>
int main(int argc, char *argv[])
{
  try
  {
    dimkashelk::labList1(std::cin, std::cout, argc, argv);
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
