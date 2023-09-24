#include "functionalObjects.h"
#include <stdexcept>
#include <limits>

fesenko::IntSummator::IntSummator():
  sum_(0)
{}

void fesenko::StrSummator::operator()(const std::pair< int, std::string > &value_type)
{
  if (sum_ > 0 && value_type.first > 0 && sum_ > std::numeric_limits< int >::max() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  if (sum_ < 0 && value_type.first < 0 && sum_ < std::numeric_limits< int >::min() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  sum_ += value_type.first;
}

int fesenko::IntSummator::getSum() const
{
  return sum_;
}

fesenko::StrSummator::StrSummator():
  sum_("")
{}

void fesenko::StrSummator::operator()(const std::pair< int, std::string > &value_type)
{
  if (sum_.max_size() - sum_.size() < value_type.second.size()) {
    throw std::overflow_error("Overflow");
  }
  if (sum_.size() != 0) {
    sum_ += " ";
  }
  sum_ += value_type.second;
}

std::string fesenko::StrSummator::getSum() const
{
  return sum_;
}
