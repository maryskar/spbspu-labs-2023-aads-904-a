#include "owerflowlongcheck.h"
#include <limits>
constexpr long long maxLongLong = std::numeric_limits< long long >::max();
constexpr long long minLongLong = std::numeric_limits< long long >::min();
namespace romanovich
{
  int signum(long long n)
  {
    return (n > 0) - (n < 0);
  }
}
bool romanovich::overflowAdd(long long a, long long b)
{
  if (signum(a) == signum(b))
  {
    return ((b > 0 && a > maxLongLong - b) || (b < 0 && a < minLongLong - b));
  }
  return false;
}
bool romanovich::overflowMult(long long a, long long b)
{
  return ((a != 0 && b != 0) && ((a > maxLongLong / b) || (a < minLongLong / b)));
}
bool romanovich::overflowSubt(long long a, long long b)
{
  return ((b < 0 && a > maxLongLong + b) || (b > 0 && a < minLongLong + b));
}