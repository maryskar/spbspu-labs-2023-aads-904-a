#ifndef MATHFUNC_H
#define MATHFUNC_H
#include <stdexcept>
#include <limits>
namespace tarasenko
{
  long long sign(long long val)
  {
    return (val > 0) ? 1 : ((val < 0) ? -1 : 0);
  }

  bool haveSameSign(long long a, long long b)
  {
    return sign(a) * sign(b) > 0;
  }

  long long summarize(long long a, long long b)
  {
    if (b > 0 && a > std::numeric_limits< long long >::max() - b)
    {
      throw std::overflow_error("Overflow error");
    }
    if (b < 0 && a < std::numeric_limits< long long >::min() - b)
    {
      throw std::overflow_error("Overflow error");
    }
    return a + b;
  }

  long long subtract(long long a, long long b)
  {
    if (b < 0 && a > std::numeric_limits< long long >::max() + b)
    {
      throw std::overflow_error("Overflow error");
    }
    if (b > 0 && a < std::numeric_limits< long long >::min() + b)
    {
      throw std::overflow_error("Overflow error");
    }
    return a - b;
  }

  long long multiply(long long a, long long b)
  {
    if (a == 0 || b == 0)
    {
      return 0;
    }
    if (haveSameSign(a, b))
    {
      if (std::numeric_limits< long long >::max() / b > a && b > 0)
      {
        return a * b;
      }
      else if (std::numeric_limits< long long >::max() / b < a && b < 0)
      {
        return a * b;
      }
    }
    else
    {
      if (std::numeric_limits< long long >::min() / b < a && b > 0)
      {
        return a * b;
      }
      else if (std::numeric_limits< long long >::min() / b > a && b < 0)
      {
        return a * b;
      }
    }
    throw std::overflow_error("Overflow error");
  }

  long long divide(long long a, long long b)
  {
    if (b == 0)
    {
      throw std::logic_error("Division by zero");
    }
    if (a == std::numeric_limits< long long >::min() && b == -1)
    {
      throw std::logic_error("Overflow error");
    }
    return a / b;
  }

  long long mod(long long a, long long b)
  {
    if (b == -1)
    {
      return 0;
    }
    long long result = a % b;
    if (sign(result) * sign(b) < 0)
    {
      result = summarize(result, b);
    }
    return result;
  }
}
#endif
