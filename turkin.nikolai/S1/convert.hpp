#ifndef CONVERT_HPP
#define CONVERT_HPP

#include "data-type.hpp"
#include <stdexcept>

namespace
{
  turkin::PFIX inf2fix(turkin::PINF rhs)
  {
    if (rhs == turkin::PINF::LEFT_BRACKET || rhs == turkin::PINF::RIGHT_BRACKET)
    {
      throw std::runtime_error("expression error");
    }
    return static_cast< turkin::PFIX >(rhs);
  }

  turkin::PINF fix2inf(turkin::PFIX rhs)
  {
    return static_cast< turkin::PINF >(rhs);
  }
};

namespace turkin
{
  turkin::calc_t< turkin::PINF > convertFIX2INF(const turkin::calc_t < turkin::PFIX > & rhs)
  {
    return turkin::calc_t< turkin::PINF >(rhs.getNum(), fix2inf(rhs.getType()));
  }

  turkin::calc_t< turkin::PFIX > convertINF2FIX(const turkin::calc_t < turkin::PINF > & rhs)
  {
    return turkin::calc_t< turkin::PFIX >(rhs.getNum(), inf2fix(rhs.getType()));
  }
};

#endif
