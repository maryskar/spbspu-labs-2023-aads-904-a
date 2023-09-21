#ifndef S6_SORT_COMMANDS_H
#define S6_SORT_COMMANDS_H

#include <iostream>
#include <string>
#include <functional>
#include <map.h>
#include "funcs_for_sort_commands.h"

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
