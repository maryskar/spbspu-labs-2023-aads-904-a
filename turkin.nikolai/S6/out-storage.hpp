#ifndef OUT_STORAGE_HPP
#define OUT_STORAGE_HPP

#include <ostream>

namespace turkin
{
  template< typename ForwardIt >
  std::ostream & out_storage(ForwardIt first, ForwardIt last, std::ostream & out)
  {
    for (auto it = first; it != last; it++)
    {
      if (it != first)
      {
        out << " ";
      }
      out << *it;
    }
    return out;
  }
}

#endif
