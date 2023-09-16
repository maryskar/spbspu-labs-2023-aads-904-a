#include "arithmetic.hpp"
#include <cmath>
#include <stdexcept>
#include <limits>

constexpr long double max = std::numeric_limits< long double >::max();
constexpr long double min = std::numeric_limits< long double >::lowest();

long double hrushchev::sum(long double a, long double b)
{
  if (max - a < b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b;
}

long double hrushchev::subtract(long double a, long double b)
{
  if ((b > 0) && (min + b > a))
  {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

long double hrushchev::multiply(long double a, long double b)
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

long double hrushchev::division(long double a, long double b)
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

long double hrushchev::sin(double a)
{
  return std::sin(a);
}

long double hrushchev::cos(double a)
{
  return std::cos(a);
}
