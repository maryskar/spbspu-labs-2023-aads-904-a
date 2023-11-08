#include "ExprProcessFunctions.h"
#include <cmath>
#include <stdexcept>
#include <limits>

namespace skarlygina
{
  long long MAX = std::numeric_limits< long long >::max();
  long long MIN = std::numeric_limits< long long >::min();
  bool isOvflSum(long long, long long);
  bool isUnflSum(long long, long long);
  bool isOvflMult(long long, long long);
  bool isUnflMult(long long, long long);
  bool isSumOverflow(long long lhs, long long rhs)
  {
    return isOvflSum(lhs, rhs) || isUnflSum(lhs, rhs);
  }
  bool isMultOverflow(long long lhs, long long rhs)
  {
    return isOvflMult(lhs, rhs) || isUnflMult(lhs, rhs);
  }
  bool isDivOverflow(long long lhs, long long rhs)
  {
    return lhs == MIN && rhs == -1;
  }
  long long sum(long long lhs, long long rhs)
  {
    if (isSumOverflow(lhs, rhs))
    {
      throw std::overflow_error("Arithmetic overflow occured");
    }
    return lhs + rhs;
  }
  long long substract(long long lhs, long long rhs)
  {
    if (isSumOverflow(lhs, -rhs))
    {
      throw std::overflow_error("Arithmetic overflow occured");
    }
    return lhs - rhs;
  }
  long long divide(long long lhs, long long rhs)
  {
    if (isDivOverflow(lhs, rhs))
    {
      throw std::overflow_error("Arithmetic overflow occured");
    }
    if (!rhs)
    {
      throw std::logic_error("Division by zero");
    }
    return lhs / rhs;
  }
  long long multiply(long long lhs, long long rhs)
  {
    if (isMultOverflow(lhs, rhs))
    {
      throw std::overflow_error("Arithmetic overflow occured");
    }
    return lhs * rhs;
  }
  long long moduloOperation(long long lhs, long long rhs)
  {
    if (!rhs)
    {
      throw std::logic_error("Division by zero");
    }
    else if ((lhs > 0 && rhs > 0) || (lhs > 0 && rhs < 0))
    {
      return lhs % std::abs(rhs);
    }
    else
    {
      return lhs - rhs * (divide(lhs, rhs) - 1);
    }
  }
  bool isHighPrecedenceOperator(char c)
  {
    return c == '*' || c == '/' || c == '%';
  }
  bool isLowPrecedenceOperator(char c)
  {
    return c == '+' || c == '-';
  }
  bool isOvflSum(long long lhs, long long rhs)
  {
    return lhs > 0 && rhs > 0 && (MAX - lhs < rhs);
  }
  bool isUnflSum(long long lhs, long long rhs)
  {
    return lhs < 0 && rhs < 0 && (MIN + std::abs(lhs) > rhs);
  }
  bool isSameSign(long long lhs, long long rhs)
  {
    return (lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0);
  }
  bool isDiffSign(long long lhs, long long rhs)
  {
    return (lhs > 0 && rhs < 0) || (lhs < 0 && rhs > 0);
  }
  bool isOvflMult(long long lhs, long long rhs)
  {
    return isSameSign(lhs, rhs) && (MAX / std::abs(lhs) < std::abs(rhs));
  }
  bool isUnflMult(long long lhs, long long rhs)
  {
    return isDiffSign(lhs, rhs) && (MIN / std::abs(lhs) > -std::abs(rhs));
  }
}

