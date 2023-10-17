#include "key-summator.hpp"
#include <string>
#include <overflows-of-long.hpp>

chemodurov::KeySummator::KeySummator():
 sum_(0)
{}

void chemodurov::KeySummator::operator()(const std::pair< const long, std::string > & pair)
{
  sum_ = calcSum(sum_, pair.first);
}

long chemodurov::KeySummator::getSum() const
{
  return sum_;
}
