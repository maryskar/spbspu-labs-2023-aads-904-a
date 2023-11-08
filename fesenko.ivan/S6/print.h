#ifndef PRINT_H
#define PRINT_H
#include <ostream>
namespace fesenko
{
  template< typename ForwardIt >
  std::ostream &print(ForwardIt first, ForwardIt last, std::ostream &out)
  {
    for (auto it = first; it != last; it++) {
      if (it != first) {
        out << " ";
      }
      out << *it;
    }
    return out;
  }
}
#endif
