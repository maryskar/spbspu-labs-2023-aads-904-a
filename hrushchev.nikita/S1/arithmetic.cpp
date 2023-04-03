#include "arithmetic.hpp"
#include <stdexcept>
#include <limits>

long long sum(long long a, long long b)
{
  const long long max = std::numeric_limits< int long long >::max();
  if(max - a < b)
  {
    throw std::overflow_error("Sum overflow");
  }
  return a + b;
}

long long subtract(long long a, long long b)
{
  const long long min = std::numeric_limits<long long>::min();
  if (b > 0 && a < min + b) {
    throw std::overflow_error("Subtraction overflow");
  }
  if (b < 0 && a > min + b) {
    throw std::overflow_error("Subtraction overflow");
  }
  return a - b;
}

long long multiply(long long a, long long b)
{
  const long long max = std::numeric_limits< int long long >::max();
  const long long min = std::numeric_limits< int long long >::min();
  if((a > 0) && ((max / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if((a < 0) && ((max / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if((a > 0) && ((min / a) > b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  else if((a < 0) && ((min / a) < b))
  {
    throw std::overflow_error("Multiply overflow");
  }
  return a * b;
}

long long division(long long a, long long b)
{
  if(b == 0)
  {
    throw std::logic_error("Division by 0");
  }
  return a / b;
}

long long remaind(long long a, long long b)
{
  if(b == 0)
  {
    throw std::logic_error("Remaind by 0");
  }
  return a % b;
}

