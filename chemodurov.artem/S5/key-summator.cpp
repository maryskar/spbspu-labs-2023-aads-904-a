#include "key-summator.hpp"
#include <string>
#include <limits>
#include <stdexcept>

chemodurov::KeySummator::KeySummator():
 sum_(0)
{}

void chemodurov::KeySummator::operator()(const std::pair< const int, std::string > & pair)
{
  sum_ = calcSum(sum_, pair.first);
}

int chemodurov::KeySummator::getSum() const
{
  return sum_;
}

bool isSameSign(int lhs, int rhs)
{
  return ((lhs > 0 && rhs > 0) || (lhs < 0 && rhs < 0));
}

int chemodurov::calcSum(int lhs, int rhs)
{
  const long max_long = std::numeric_limits< int >::max();
  const long min_long = std::numeric_limits< int >::min();
  if (isSameSign(lhs, rhs) && lhs > 0 && max_long - lhs < rhs)
  {
    throw std::overflow_error("Overflow in sum");
  }
  if (isSameSign(lhs, rhs) && lhs < 0 && min_long - lhs > rhs)
  {
    throw std::overflow_error("Underflow in sum");
  }
  return lhs + rhs;
}

