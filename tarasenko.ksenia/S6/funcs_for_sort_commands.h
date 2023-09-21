#ifndef S6_FUNCS_FOR_SORT_COMMANDS_H
#define S6_FUNCS_FOR_SORT_COMMANDS_H
#include <iostream>

namespace tarasenko
{
  std::ostream& sortAscendingInts(std::ostream& out, size_t num_of_val);
  std::ostream& sortDescendingInts(std::ostream& out, size_t num_of_val);
  std::ostream& sortAscendingFloats(std::ostream& out, size_t num_of_val);
  std::ostream& sortDescendingFloats(std::ostream& out, size_t num_of_val);
}
#endif
