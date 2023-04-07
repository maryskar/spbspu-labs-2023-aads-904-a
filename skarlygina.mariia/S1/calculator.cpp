#include "calculator.h"
#include <limits>
#include <cmath>
#include <stdexcept>

long long calculator::sum(long long a, long long b)
{
  constexpr long long limit = std::numeric_limits< long long >::max();
  if (limit - a < b)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a + b;
}

long long calculator::substraction(long long a, long long b)
{
  constexpr long long limit = std::numeric_limits< long long >::min();
  if (limit + b > a)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a - b;
}