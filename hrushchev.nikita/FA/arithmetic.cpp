#include "arithmetic.hpp"
#include <cmath>
#include <stdexcept>
#include <limits>

constexpr long long max = std::numeric_limits< long long >::max();
constexpr long long min = std::numeric_limits< long long >::min();

long double hrushchev::sum(long long a, long long b)
{
  if (max - a < b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b;
}

long double hrushchev::subtract(long long a, long long b)
{
  if ((b > 0) && (min + b > a))
  {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

long double hrushchev::multiply(long long a, long long b)
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

long double hrushchev::division(long long a, long long b)
{
  if (b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  return a / b;
}

long double hrushchev::remaind(long long a, long long b)
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

long double hrushchev::sin(double a)
{
  return std::sin(a);
}

long double hrushchev::cos(double a)
{
  return std::cos(a);
}
