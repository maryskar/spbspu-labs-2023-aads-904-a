#include "calculator.h"
#include <limits>
#include <cmath>
#include <stdexcept>

constexpr long long limit_min = std::numeric_limits< long long >::min();
constexpr long long limit_max = std::numeric_limits< long long >::max();

long long calculator::sum(long long a, long long b)
{
  if (limit_max - a < b)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a + b;
}

long long calculator::substraction(long long a, long long b)
{
  if (limit_min + b > a)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a - b;
}

long long calculator::multiplication(long long a, long long b)
{
  if ((b > 0 && a > limit_max / b) || (b < 0 && a < limit_min / b))
  {
    throw std::overflow_error("Multiplication overflow");
  }
  return a * b;
}

long long calculator::division(long long a, long long b)
{
  if (b == 0)
  {
    throw std::invalid_argument("Division by zero");
  }
  if ((b > 0 && a > limit_max / b) || (b < 0 && a < limit_min / b))
  {
    throw std::overflow_error("Division overflow");
  }
  return a / b;
}

long long calculator::remainder(long long a, long long b)
{
  if (b == 0)
  {
    throw std::invalid_argument("Division by zero");
  }
  if (a == limit_min && b == -1)
  {
    throw std::overflow_error("Modulo overflow");
  }
  return a % b;
}
