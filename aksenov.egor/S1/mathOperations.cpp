#include "mathOperations.h"
#include <limits>
#include <stdexcept>
constexpr long long max = std::numeric_limits< long long >::max();
constexpr long long min = std::numeric_limits< long long >::min();
long long aksenov::sum(long long lhs, long long rhs)
{
  if (lhs > max - rhs)
  {
    throw std::overflow_error("overflow in sum");
  }
  return lhs + rhs;
}

long long aksenov::substract(long long lhs, long long rhs)
{
  if (min + rhs > lhs)
  {
    throw std::underflow_error("substract underflow");
  }
  return lhs - rhs;
}

long long aksenov::multiply(long long lhs, long long rhs)
{
  if (lhs > max)
}
