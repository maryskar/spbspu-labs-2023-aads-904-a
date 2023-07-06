#include "mathOperations.h"
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

