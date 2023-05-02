#include "calculate.h"
#include <stdexcept>
#include <limits>

namespace kryuchkova
{
  bool isSameSign(long long lhs, long long rhs)
  {
    return ((lhs < 0 && rhs < 0) || (lhs > 0 && rhs > 0));
  }

  long long calcSum(long long lhs, long long rhs)
  {
    long long max = std::numeric_limits< long long >::max();
    long long min = std::numeric_limits< long long >::min();
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
    long long max = std::numeric_limits< long long >::max();
    long long min = std::numeric_limits< long long >::min();
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
  
  long long calcMulti(long long lhs, long long rhs);
  long long calcDiv(long long lhs, long long rhs);
  long long calcEucDiv(long long lhs, long long rhs);
}