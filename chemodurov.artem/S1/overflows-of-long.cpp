#include "overflows-of-long.hpp"
#include <limits>
#include <stdexcept>

bool isSameSign(long lhs, long rhs)
{
  return ((lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0));
}

long chemodurov::calcSum(long lhs, long rhs)
{
  const long max_long = std::numeric_limits< long >::max();
  const long min_long = std::numeric_limits< long >::min();
  if (isSameSign(lhs, rhs) && lhs > 0 && max_long - lhs < rhs)
  {
    throw std::overflow_error("Overflow in sum");
  }
  if (isSameSign(lhs, rhs) && lhs < 0 && min_long - lhs > rhs)
  {
    throw std::overflow_error("Overflow in sum");
  }
  return lhs + rhs;
}

long chemodurov::calcDiff(long lhs, long rhs)
{
  const long max_long = std::numeric_limits< long >::max();
  const long min_long = std::numeric_limits< long >::min();
  if (!isSameSign(lhs, rhs) && lhs > 0 && max_long + rhs < lhs)
  {
    throw std::overflow_error("Overflow in diff");
  }
  if (!isSameSign(lhs, rhs) && lhs < 0 && min_long + rhs > lhs)
  {
    throw std::overflow_error("Overflow in diff");
  }
  return lhs - rhs;
}

long chemodurov::calcMultiplication(long lhs, long rhs)
{
  const long max_long = std::numeric_limits< long >::max();
  const long min_long = std::numeric_limits< long >::min();
  if (isSameSign(lhs, rhs) && max_long / lhs < rhs)
  {
    throw std::overflow_error("Overflow in multiplication");
  }
  if (!isSameSign(lhs, rhs) && lhs != 0 && min_long / lhs > rhs)
  {
    throw std::overflow_error("Overflow in multiplication");
  }
  return lhs * rhs;
}

long chemodurov::calcDivision(long lhs, long rhs)
{
  if (rhs == 0)
  {
    throw std::invalid_argument("Division by zero");
  }
  return lhs / rhs;
}

long chemodurov::calcReminderOfDivision(long lhs, long rhs)
{
  long result = lhs % rhs;
  if (lhs * rhs < 0)
  {
    result += rhs;
  }
  return result;
}
