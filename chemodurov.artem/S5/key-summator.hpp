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
    void operator()(const std::pair< const long, std::string > & pair);
    long getSum() const;
   private:
    long sum_;
  };
}

#endif
