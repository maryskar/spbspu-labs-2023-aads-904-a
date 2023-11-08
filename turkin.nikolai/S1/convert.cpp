#include "convert.hpp"

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
}

turkin::calc_t< turkin::PINF > turkin::convertFIX2INF(const calc_t< PFIX > & rhs)
{
  return calc_t< PINF >(rhs.getNum(), fix2inf(rhs.getType()));
}

turkin::calc_t< turkin::PFIX > turkin::convertINF2FIX(const calc_t< PINF > & rhs)
{
  return calc_t< PFIX >(rhs.getNum(), inf2fix(rhs.getType()));
}
