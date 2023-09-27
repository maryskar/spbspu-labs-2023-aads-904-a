#include <iostream>
#include <algorithm>
#include <forwardlist.hpp>
#include <functional>
#include "filllist.hpp"
#include "sortandprint.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "Error arg\n";
    return 1;
  }

  std::function< bool(int, int) > comp = std::less< >();
  if (std::string(argv[1]) == "descending")
  {
    comp = std::greater< >();
  }
  else if (std::string(argv[1]) != "ascending")
  {
    std::cerr << "Invalid compare\n";
    return 1;
  }

  size_t size = std::stoull((argv[3]));
  if (size < 1)
  {
    std::cerr << "Invalid size\n";
    return 1;
  }

  if (std::string(argv[2]) == "ints")
  {
    hrushchev::ForwardList < int > my_list;
    hrushchev::fillRandomInts(my_list, size);
    hrushchev::sortAndPrint(std::cout, my_list, comp);
  }
  else if ((std::string(argv[2]) == "floats"))
  {
    hrushchev::ForwardList < float > my_list;
    hrushchev::fillRandomFloats(my_list, size);
    hrushchev::sortAndPrint(std::cout, my_list, comp);
  }
}
