#include "arithmetic.hpp"
#include <stdexcept>
#include <limits>

constexpr long long max = std::numeric_limits< long long >::max();
constexpr long long min = std::numeric_limits< long long >::min();

long long hrushchev::sum(long long a, long long b)
{
  if (max - a < b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b;
}

long long hrushchev::subtract(long long a, long long b)
{
  if ((b > 0) && (min + b > a))
  {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

long long hrushchev::multiply(long long a, long long b)
{
  if ((a > 0) && ((max / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a < 0) && ((max / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a > 0) && ((min / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if ((a < 0) && ((min / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  return a * b;
}

long long hrushchev::division(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  return a / b;
}

long long hrushchev::remaind(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Remaind by 0");
  }
  if (a < 0)
  {
    return b + a % b;
  }
  return a % b;
}

