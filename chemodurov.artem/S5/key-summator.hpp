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
    int getSumm() const;
   private:
    int summ_;
  };

  int calcSumm(int lhs, int rhs);
}

#endif
