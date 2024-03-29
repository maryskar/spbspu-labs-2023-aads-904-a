#include "calculate.h"
#include <stdexcept>
#include <limits>

namespace kryuchkova
{

  constexpr long long max = std::numeric_limits< long long >::max();
  constexpr long long min = std::numeric_limits< long long >::min();

  bool isSameSign(long long lhs, long long rhs)
  {
    return ((lhs < 0 && rhs < 0) || (lhs > 0 && rhs > 0));
  }

  long long calcSum(long long lhs, long long rhs)
  {
    if (isSameSign(lhs, rhs) && rhs > 0 && max - rhs < lhs)
    {
      throw std::overflow_error("Overflow");
    }
    if (isSameSign(lhs, rhs) && rhs < 0 && min - rhs > lhs)
    {
      throw std::overflow_error("Underflow");
    }
    return lhs + rhs;
  }

  long long calcDiff(long long lhs, long long rhs)
  {
    if (!isSameSign(lhs, rhs) && lhs > 0 && max + rhs < lhs)
    {
      throw std::overflow_error("Overflow");
    }
    if (!isSameSign(lhs, rhs) && lhs < 0 && min + rhs > lhs)
    {
      throw std::overflow_error("Underflow");
    }
    return lhs - rhs;
  }

  long long calcMulti(long long lhs, long long rhs)
  {
    if (isSameSign(lhs, rhs) && lhs > 0 && max / lhs < rhs)
    {
      throw std::overflow_error("Overflow");
    }
    if (!isSameSign(lhs, rhs) && lhs > 0 && min / lhs > rhs)
    {
      throw std::overflow_error("Underflow");
    }
    if (!isSameSign(lhs, rhs) && lhs < 0 && min / lhs < rhs)
    {
      throw std::overflow_error("Underflow");
    }
    return lhs * rhs;
  }

  long long calcDiv(long long lhs, long long rhs)
  {
    if (rhs == 0)
    {
      throw std::logic_error("Div by 0");
    }
    return lhs / rhs;
  }

  long long calcEucDiv(long long lhs, long long rhs)
  {
    long long res = lhs % rhs;
    if (lhs * rhs < 0)
    {
      res += rhs;
    }
    return res;
  }
}
