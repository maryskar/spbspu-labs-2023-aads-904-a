#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
#include "details.h"

int main(int argc, char *argv[])
{
  if (argc > 2)
  {
    std::cerr << "err" << "\n";
    return 1;
  }
  aksenov::Stack< long long > result;
  if (argc == 1)
  {
    try
    {
      aksenov::processInput(std::cin, result);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  if (argc == 2)
  {
    try
    {
      std::ifstream f;
      f.open(argv[1]);
      if (!f.is_open())
      {
        std::cerr << "cant open file" << "\n";
        return 2;
      }
      aksenov::processInput(f, result);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  aksenov::out(std::cout, result);
  std::cout << "\n";
}
