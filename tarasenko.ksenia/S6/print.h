#ifndef S6_PRINT_H
#define S6_PRINT_H
#include <iostream>

namespace tarasenko
{
  template< typename OutputIter >
  std::ostream& print(OutputIter first, OutputIter last, std::ostream& out)
  {
    if (first != last)
    {
      out << *first++;
      while (first != last)
      {
        out << " " << *first++;
      }
    }
    return out;
  }
}
#endif
