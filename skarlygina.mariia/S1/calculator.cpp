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
  return a * b;
}

long long calculator::division(long long a, long long b)
{
  return a / b;
}

long long calculator::remainder(long long a, long long b)
{
  return a % b;
}
