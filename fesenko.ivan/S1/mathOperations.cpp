#include "mathOperations.h"
#include <stdexcept>
#include <limits>
long long fesenko::summarize(long long a, long long b)
{
  if (a > 0 && b > 0 && a > std::numeric_limits< long long >::max() - b) {
    throw std::overflow_error("Overflow");
  }
  if (a < 0 && b < 0 && a < std::numeric_limits< long long >::min() - b) {
    throw std::overflow_error("Overflow");
  }
  return a + b;
}

long long fesenko::subtract(long long a, long long b)
{
  return summarize(a, -b);
}

long long fesenko::multiply(long long a, long long b)
{
  if (a == 0 || b == 0) {
    return 0;
  }
  if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
    if (a > std::numeric_limits< long long >::max() / b && b < 0) {
      return a * b;
    }
    if (a < std::numeric_limits< long long >::max() / b && b > 0) {
      return a * b;
    }
  } else {
    if (b == -1 || (a < std::numeric_limits< long long >::min() / b && b < 0)) {
      return a * b;
    }
    if (a > std::numeric_limits< long long >::min() / b && b > 0) {
      return a * b;
    }
  }
  throw std::overflow_error("Overflow");

}

long long fesenko::divide(long long a, long long b)
{
  if (b == 0) {
    throw std::logic_error("Divide by zero");
  }
  return a / b;
}

long long fesenko::mod(long long a, long long b)
{
  if (b == 0) {
    throw std::logic_error("Divide by zero");
  }
  return a % b;
}
