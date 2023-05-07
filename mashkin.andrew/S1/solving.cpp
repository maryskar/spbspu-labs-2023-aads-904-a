#include "solving.h"
#include <limits>
#include <stdexcept>

constexpr int long long MAX = std::numeric_limits< int long long >::max();
constexpr int long long MIN = std::numeric_limits< int long long >::min();
int long long sign(int long long val)
{
  return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
}

bool same_sign(int long long a, int long long b)
{
  return sign(a) * sign(b) >= 0;
}

int long long mashkin::sum(int long long a, int long long b)
{
  if (same_sign(a, b) && (a >= 0))
  {
    if (MAX - a >= b)
    {
      return a + b;
    }
    else
    {
      throw std::overflow_error("Signed overflow");
    }
  }
  if (same_sign(a, b) && (a <= 0))
  {
    if (MIN - a <= b)
    {
      return a + b;
    }
    else
    {
      throw std::underflow_error("Signed underflow");
    }
  }
  else
  {
    return a + b;
  }
}

int long long mashkin::multiplicate(long long a, long long b)
{
  if (same_sign(a, b) && (a >= 0))
  {
    if (MAX / a >= b)
    {
      return a * b;
    }
    else
    {
      throw std::overflow_error("Signed overflow");
    }
  }
  if (!same_sign(a, b) && (a <= 0))
  {
    if (MIN / a >= b)
    {
      return a * b;
    }
    else
    {
      throw std::underflow_error("Signed underflow");
    }
  }
  else
  {
    return a * b;
  }
}

int long long mashkin::divide(long long a, long long b)
{
  if (a >= 0)
  {
    return a % b;
  }
  else
  {
    return a % b + b;
  }
}
