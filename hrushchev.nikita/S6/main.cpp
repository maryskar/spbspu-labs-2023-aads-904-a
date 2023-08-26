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

int main()
{
  hrushchev::ForwardList < int > my_list;
  hrushchev::fillRandomInts(my_list, 10);
  hrushchev::sortAndPrint(std::cout, my_list, std::less< >());

}
