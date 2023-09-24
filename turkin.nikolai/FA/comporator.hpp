#ifndef COMPORATOR_HPP
#define COMPORATOR_HPP

#include <utility>
#include "data-types.hpp"

namespace turkin
{
  struct SortByFreq
  {
    bool operator()(const std::pair< char, node_t * > & lhs, const std::pair< char, node_t * > rhs);
  };
}

#endif
