#include "calc-verify.hpp"
#include <limits>

bool turkin::verify::isADDerror(long long lhs, long long rhs) noexcept
{
  return lhs > 0 && rhs > 0 && (lhs + rhs < 0);
}

bool turkin::verify::isSUBerror(long long lhs, long long rhs) noexcept
{
  return lhs < 0 && rhs < 0 && (lhs + rhs > 0);
}

bool turkin::verify::isMULerror(long long lhs, long long rhs) noexcept
{
  long long maxLL = std::numeric_limits< long long >::max();
  long long minLL = std::numeric_limits< long long >::min();
  bool over = (lhs > maxLL / rhs) && ((lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0));
  bool under = (lhs < minLL / rhs) && ((lhs > 0 && rhs < 0) || (lhs < 0 && rhs > 0));
  return over || under;
}

bool turkin::verify::isDIVerror(long long lhs, long long rhs) noexcept
{
  return lhs == 0 || rhs == 0;
}

bool turkin::verify::isMODerror(long long lhs, long long rhs) noexcept
{
  return isDIVerror(lhs, rhs);
}
