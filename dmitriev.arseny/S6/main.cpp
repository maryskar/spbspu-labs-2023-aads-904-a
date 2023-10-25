#include <iostream>
#include <functional>
#include <string>

#include "printSortData.h"


int main(int argc, char** argv)
{
  if (argc != 4)
  {
    std::cout << "trror arg" << '\n';
    return 1;
  }

  std::function< bool(int, int) > comp;
  if (std::string(argv[1]) == "descending")
  {
    comp = std::greater_equal< >();
  }
  else if (std::string(argv[1]) == "ascending")
  {
    comp = std::less_equal< >();
  }

  size_t size = 0;
  try
  {
    size = std::stoull((argv[3]));
  }
  catch (const std::exception&)
  {
    std::cout << "invalid number" << '\n';
    return 1;
  }
  if (size < 1)
  {
    std::cerr << "invalid size" << '\n';
    return 1;
  }

  if (std::string(argv[2]) == "ints")
  {
    dmitriev::printSortData< int >(size, std::cout, comp);
  }
  else if (std::string(argv[2]) == "floats")
  {
    dmitriev::printSortData< float >(size, std::cout, comp);
  }
  else
  {
    std::cerr << "invalid data type" << '\n';
    return 1;
  }

  return 0;
}
