#ifndef FA_COMPARE_H
#define FA_COMPARE_H

#include <functional>

namespace tarasenko
{
  namespace details
  {
    union CompType
    {
      std::less<> less;
      std::greater<> greater;
    };
  }

  class Comp
  {
  public:
   Comp():
     comp_{std::less<>{}},
     is_less(true)
   {}

   explicit Comp(std::less<> less):
     comp_{std::less<>{}},
     is_less(true)
   {}

   explicit Comp(std::greater<> greater):
     comp_{std::less<>{}},
     is_less(false)
   {
     comp_.greater = greater;
   }

   template< class T >
   bool operator()(const T& lhs, const T& rhs) const
   {
     if (is_less)
     {
       return lhs < rhs;
     }
     return lhs > rhs;
   }

  private:
   details::CompType comp_;
   bool is_less;
  };
}

#endif
