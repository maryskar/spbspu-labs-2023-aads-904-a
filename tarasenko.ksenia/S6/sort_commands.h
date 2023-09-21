#ifndef S6_SORT_COMMANDS_H
#define S6_SORT_COMMANDS_H
#include <iostream>
#include <string>
#include <functional>
#include <map.h>
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

namespace tarasenko
{
  template< typename Compare = std::less<> >
  class Commands
  {
  public:
   Commands():
     cms()
   {
     cms.push("ascending ints", &sortAscendingInts);
     cms.push("descending ints", &sortDescendingInts);
     cms.push("ascending floats", &sortAscendingFloats);
     cms.push("descending floats", &sortDescendingFloats);
   }

   std::function< std::ostream&(std::ostream&, size_t) >& at(const std::string& command)
   {
     return cms.at(command);
   }

  private:
   Map< std::string, std::function< std::ostream&(std::ostream&, size_t) >, Compare > cms;
  };
}
#endif
