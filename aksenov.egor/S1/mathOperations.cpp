#include "mathOperations.h"
#include <limits>
#include <stdexcept>
constexpr long long max = std::numeric_limits< long long >::max();
constexpr long long min = std::numeric_limits< long long >::min();
long long aksenov::sum(long long lhs, long long rhs)
{
  if (lhs >= max - rhs)
  {
    throw std::overflow_error("overflow in sum");
  }
  return lhs + rhs;
}

long long aksenov::substract(long long lhs, long long rhs)
{
  if (min + rhs > lhs && rhs > 0)
  {
    throw std::underflow_error("substract underflow");
  }
  return lhs - rhs;
}

long long aksenov::multiply(long long lhs, long long rhs)
{
  if ((lhs > 0 && rhs > 0) && (lhs > max / rhs))
  {
    throw std::overflow_error("overflow in multiply");
  }
  if ((lhs > 0 && rhs < 0 ) && (lhs > min / rhs))
  {
    throw std::underflow_error("underflow in multiply");
  }
  if ((lhs < 0 && rhs < 0) && (lhs < max / rhs))
  {
    throw std::overflow_error("overflow in multiply");
  }
  if ((lhs < 0 && rhs > 0) && (lhs < min / rhs))
  {
    throw std::underflow_error("underflow in multiply");
  }
  else
  {
    return lhs * rhs;
  }
}

long long aksenov::divide(long long lhs, long long rhs)
{
  if (rhs == 0)
  {
    throw std::invalid_argument("division on zero");
  }
  else
  {
    return lhs / rhs;
  }
}

long long aksenov::remaind(long long lhs, long long rhs)
{
  if (rhs == 0)
  {
    throw std::invalid_argument("division on zero");
  }
  if (lhs < 0)
  {
    return rhs + lhs % rhs;
  }
  return lhs % rhs;
}
