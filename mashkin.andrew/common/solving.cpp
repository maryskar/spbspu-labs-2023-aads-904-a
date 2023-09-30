#include "solving.h"
#include <limits>
#include <stdexcept>

namespace mashkin
{
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

  int long long sum(int long long first, int long long second)
  {
    if (same_sign(first, second) && (first >= 0))
    {
      if (MAX - first >= second)
      {
        return first + second;
      }
      else
      {
        throw std::overflow_error("Signed overflow");
      }
    }
    if (same_sign(first, second) && (first <= 0))
    {
      if (MIN - first <= second)
      {
        return first + second;
      }
      else
      {
        throw std::underflow_error("Signed underflow");
      }
    }
    else
    {
      return first + second;
    }
  }

  int long long minus(long long first, long long second)
  {
    return sum(first, second * (-1));
  }

  int long long divide(long long first, long long second)
  {
    if (second == 0)
    {
      throw std::logic_error("Division by zero");
    }
    return first / second;
  }

  int long long multiplicate(long long first, long long second)
  {
    if (same_sign(first, second) && (first >= 0))
    {
      if (MAX / first >= second)
      {
        return first * second;
      }
      else
      {
        throw std::overflow_error("Signed overflow");
      }
    }
    if (!same_sign(first, second) && (first <= 0))
    {
      if (MIN / first >= second)
      {
        return first * second;
      }
      else
      {
        throw std::underflow_error("Signed underflow");
      }
    }
    else
    {
      return first * second;
    }
  }

  int long long getRemainderAfterDivision(long long first, long long second)
  {
    if (first >= 0)
    {
      return first % second;
    }
    else
    {
      return first % second + second;
    }
  }

  int long long exponentiate(long long first, long long second)
  {
    for (auto i = 0; i < second; i++)
    {
      first = multiplicate(first, first);
    }
    return first;
  }

  int long long factorial(long long first, long long)
  {
    if (first < 0)
    {
      throw std::logic_error("Factorial can't be less than 0");
    }
    if (first == 0)
    {
      return 1;
    }
    long long res = 1;
    for (auto i = 1; i <= first; i++)
    {
      res = multiplicate(res, i);
    }
    return res;
  }
}
