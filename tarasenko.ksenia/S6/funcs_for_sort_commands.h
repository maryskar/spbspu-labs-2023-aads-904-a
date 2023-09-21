#ifndef S6_FUNCS_FOR_SORT_COMMANDS_H
#define S6_FUNCS_FOR_SORT_COMMANDS_H
#include <iostream>
#include <forward_list.h>
#include "fill_random.h"
#include "print_sorts.h"

namespace tarasenko
{
  std::ostream& sortAscendingInts(std::ostream& out, size_t num_of_val)
  {
    tarasenko::ForwardList< int > data;
    tarasenko::fillRandom(data, num_of_val);
    return printSorts(data.begin(), data.end(), std::less<>{}, out);
  }

  std::ostream& sortDescendingInts(std::ostream& out, size_t num_of_val)
  {
    tarasenko::ForwardList< int > data;
    tarasenko::fillRandom(data, num_of_val);
    return printSorts(data.begin(), data.end(), std::greater<>{}, out);
  }

  std::ostream& sortAscendingFloats(std::ostream& out, size_t num_of_val)
  {
    tarasenko::ForwardList< float > data;
    tarasenko::fillRandom(data, num_of_val);
    return printSorts(data.begin(), data.end(), std::less<>{}, out);
  }

  std::ostream& sortDescendingFloats(std::ostream& out, size_t num_of_val)
  {
    tarasenko::ForwardList< float > data;
    tarasenko::fillRandom(data, num_of_val);
    return printSorts(data.begin(), data.end(), std::greater<>{}, out);
  }
}
#endif
