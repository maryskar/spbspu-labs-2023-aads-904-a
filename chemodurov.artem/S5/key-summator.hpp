#ifndef S5_KEY_SUMMATOR_HPP
#define S5_KEY_SUMMATOR_HPP
#include <iosfwd>
#include <utility>

namespace chemodurov
{
  class KeySummator
  {
   public:
    KeySummator();
    void operator()(const std::pair< const int, std::string > & pair);
    int getSum() const;
   private:
    int sum_;
  };

  int calcSum(int lhs, int rhs);
}

#endif
