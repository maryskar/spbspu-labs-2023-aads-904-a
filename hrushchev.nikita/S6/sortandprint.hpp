#ifndef SORTANDPRINT_HPP
#define SORTANDPRINT_HPP

#include <ostream>
#include <string>
#include <stdexcept>
#include <forwardlist.hpp>

namespace hrushchev
{
  template< typename T >
  void sortAndPrint(std::ostream& out, std::string& comp_type, size_t size)
  {
    if (size <= 0)
    {
      throw std::logic_error("Incorect size");
    }

    if (comp_type == "ascending")
    {
      auto comp = std::less< >();
    }
    else if (comp_type == "descending")
    {
      auto comp = std::greater< >();
    }
    else
    {
      throw std::logic_error("Incorect comp type");
    }

    ForwardList< T > forward_list;
  }
}

#endif
