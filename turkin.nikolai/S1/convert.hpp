#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "data-type.hpp"
#include <stdexcept>

namespace turkin
{
  namespace convert
  {
    datatype::calc_t< datatype::PINF > convertFIX2INF(const datatype::calc_t < datatype::PFIX > & rhs)
    {
      if (rhs.type == datatype::PFIX::NUM)
      {
        return datatype::calc_t< datatype::PINF >(rhs.calc.num, static_cast< datatype::PINF >(rhs.type));
      }
      return datatype::calc_t< datatype::PINF >(rhs.calc.sign, static_cast< datatype::PINF >(rhs.type));
    }

    datatype::calc_t< datatype::PFIX > convertINF2FIX(const datatype::calc_t < datatype::PINF > & rhs)
    {
      if (rhs.type == datatype::PINF::LEFT_BRACKET || rhs.type == datatype::PINF::RIGHT_BRACKET)
      {
        throw std::runtime_error("expression error");
      }
      if (rhs.type == datatype::PINF::NUM)
      {
        return datatype::calc_t< datatype::PFIX >(rhs.calc.num, static_cast< datatype::PFIX >(rhs.type));
      }
      return datatype::calc_t< datatype::PFIX >(rhs.calc.sign, static_cast< datatype::PFIX >(rhs.type));
    }
  };
};

#endif
