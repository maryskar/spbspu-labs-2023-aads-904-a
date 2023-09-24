#include "functionalObjects.h"
#include <stdexcept>

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
