#include "functionalObjects.h"
#include <stdexcept>
#include <limits>

fesenko::NumSummator::NumSummator():
  sum_(0)
{}

void fesenko::NumSummator::operator()(const std::pair< long long, std::string > &value_type)
{
  if (sum_ > 0 && value_type.first > 0 && sum_ > std::numeric_limits< long long >::max() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  if (sum_ < 0 && value_type.first < 0 && sum_ < std::numeric_limits< long long >::min() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  sum_ += value_type.first;
}

long long fesenko::NumSummator::getSum() const
{
  return sum_;
}

fesenko::StrSummator::StrSummator():
  sum_("")
{}

void fesenko::StrSummator::operator()(const std::pair< long long, std::string > &value_type)
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

fesenko::Summator::Summator():
  numSum_(NumSummator()),
  strSum_(StrSummator())
{}

void fesenko::Summator::operator()(const std::pair< long long, std::string > &value_type)
{
  numSum_(value_type);
  strSum_(value_type);
}

std::pair< long long, std::string > fesenko::Summator::getSum() const
{
  return std::make_pair(numSum_.getSum(), strSum_.getSum());
}
