#ifndef COMPORATOR_HPP
#define COMPORATOR_HPP

#include <cstddef>
#include "data-types.hpp"

namespace turkin
{
  struct SortByFreq
  {
    bool operator()(const encoding_pair_t & lhs, const encoding_pair_t & rhs);
  };
}

#endif
