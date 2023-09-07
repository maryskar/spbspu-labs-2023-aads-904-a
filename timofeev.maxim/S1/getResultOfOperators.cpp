#include "getResultOfOperators.h"
#include <stdexcept>
#include <limits>
long long Max = std::numeric_limits< long long >::max();
long long Min = std::numeric_limits< long long >::min();
namespace timofeev
{
  long long getSum(long long one, long long two)
  {
    if (one > 0 && two > 0 && one > Max - two)
    {
      throw std::overflow_error("Overflow sum");
    }
    else if (one < 0 && two < 0 && one < Min - two)
    {
      throw std::underflow_error("underflow sum");
    }
    else
    {
      return one + two;
    }
  }
    long long getMinus(long long one, long long two)
  {
    if (one < 0 && two > 0 && one < Min + two)
    {
      throw std::underflow_error("underflow minus");
    }
    if (one > 0 && two < 0 && one > Max + two)
    {
      throw std::overflow_error("overflow minus");
    }
    else
    {
      return one - two;
    }
  }
    long long getDiv(long long one, long long two)
  {
    if (two == 0)
    {
      throw std::invalid_argument("div by ZERO");
    }
    if (two == -1 && one < Max * two)
    {
      throw std::overflow_error("overflow div");
    }
    else
    {
      return one / two;
    }
  }
    long long getMultip(long long one, long long two)
  {
    if (one > 0 && two > 0 && one > Max / two)
    {
      throw std::overflow_error("overflow mul");
    }
    if (one < 0 && two < 0 && one < Max / two)
    {
      throw std::overflow_error("overflow mul");
    }
    if (one < 0 && two > 0 && one < Min / two)
    {
      throw std::underflow_error("underflow mul");
    }
    if (one > 0 && two < 0 && one > Min / two)
    {
      throw std::underflow_error("underflow mul");
    }
    else
    {
      return one * two;
    }
  }
    long long getRemander(long long one, long long two)
  {
    if (two == 0)
    {
      throw std::invalid_argument("div by ZERO");
    }
    long long int ret = one % two;
    if (ret < 0)
      ret += two;
    return ret;
  }
}
