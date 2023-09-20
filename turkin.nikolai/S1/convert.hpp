#ifndef CONVERT_HPP
#define CONVERT_HPP

#include <stdexcept>
#include "data-type.hpp"

namespace turkin
{
  calc_t< PINF > convertFIX2INF(const calc_t< PFIX > & rhs);
  calc_t< PFIX > convertINF2FIX(const calc_t< PINF > & rhs);
}

#endif
