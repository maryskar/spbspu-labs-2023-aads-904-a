#include "getResultOfOperators.h"
#include <stdexcept>
#include <limits>
ll Max = std::numeric_limits<ll>::max();
ll Min = std::numeric_limits<ll>::min();
namespace timofeev
{
  ll getSum(ll one, ll two)
  {
    if (one > 0 && two > 0 && one > Max - two)
    {
      throw std::overflow_error("Overflow sum");
    }
    else if (one < 0 && two < 0 & one < Min - two)
    {
      throw std::underflow_error("underflow sum");
    }
    else
    {
      return one + two;
    }
  }
  ll getMinus(ll one, ll two)
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
  ll getDiv(ll one, ll two)
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
  ll getMultip(ll one, ll two)
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
  ll getRemander(ll one, ll two)
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
