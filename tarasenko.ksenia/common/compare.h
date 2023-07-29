#ifndef FA_COMPARE_H
#define FA_COMPARE_H

#include <functional>

namespace details
{
  union comp
  {
    std::less<> less;
    std::greater<> greater;
  };
}

struct Comp
{
  Comp():
    comp_{std::less<>{}},
    is_less(true)
  {};
  explicit Comp(const std::less<>& less):
    comp_{std::less<>{}},
    is_less(true)
  {};
  explicit Comp(const std::greater<>& greater):
    comp_{std::less<>{}},
    is_less(false)
  {
    comp_.greater = greater;
  };
  template< class T >
  bool operator()(const T& lhs, const T& rhs) const
  {
    if (is_less)
    {
      return lhs < rhs;
    }
    return lhs > rhs;
  }
  details::comp comp_;
  bool is_less;
};
#endif
