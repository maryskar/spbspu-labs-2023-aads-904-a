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

}
