#include <iostream>
#include <deque>
#include <list>
#include <algorithm>
#include <functional>
#include <random>
#include "insertion.hpp"
#include "oddeven.hpp"
#include "shaker.hpp"
#include "filllist.hpp"
#include <forwardlist.hpp>
#include "sortandprint.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "Error arg\n";
    return 1;
  }

  size_t size = std::stoull((argv[3]));
  if (size < 1)
  {
    std::cerr << "Invalid size";
    return 1;
  }

  hrushchev::ForwardList < int > my_list;
  hrushchev::fillRandomInts(my_list, size);
  hrushchev::sortAndPrint(std::cout, my_list, std::less< >());

}
