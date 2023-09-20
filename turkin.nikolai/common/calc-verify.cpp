#include "calc-verify.hpp"
#include <limits>

constexpr long long maxLL = std::numeric_limits< long long >::max();
constexpr long long minLL = std::numeric_limits< long long >::min();

bool turkin::isADDerror(long long lhs, long long rhs) noexcept
{
  return lhs > 0 && rhs > 0 && rhs > (maxLL - lhs);
}

bool turkin::isSUBerror(long long lhs, long long rhs) noexcept
{
  return lhs < 0 && rhs < 0 && lhs < (minLL - rhs);
}

bool turkin::isMULerror(long long lhs, long long rhs) noexcept
{
  bool over = (lhs > maxLL / rhs) && ((lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0));
  bool under = (lhs < minLL / rhs) && ((lhs > 0 && rhs < 0) || (lhs < 0 && rhs > 0));
  return over || under;
}

bool turkin::isDIVerror(long long lhs, long long rhs) noexcept
{
  return lhs == 0 || rhs == 0;
}

bool turkin::isMODerror(long long lhs, long long rhs) noexcept
{
  return isDIVerror(lhs, rhs);
}
