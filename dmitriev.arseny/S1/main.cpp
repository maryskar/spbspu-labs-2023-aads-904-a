#include <iostream>
#include <fstream>
#include "printRezult.h"

int main(int argv, char** argc)
{
  try
  {
    if (argv == 2)
    {
      std::ifstream file(argc[1]);
      dmitriev::printSeriesOfNumbers(file, std::cout);
    }
    else
    {
      dmitriev::printSeriesOfNumbers(std::cin, std::cout);
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << '\n';
    return 1;
  }

  return 0;
}
