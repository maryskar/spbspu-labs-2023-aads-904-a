#include "functionalObjects.h"
#include <limmits>

fesenko::StrSummator::StrSummator():
  sum_("")
{}

void fesenko::StrSummator::operator()(const std::pair< int, std::string > &value_type)
{
  if (std::numeric_limits<std::string>::max() - sum_.size() < value_type.second.size()) {
    throw std::overflow_error("Overflow");
  }
  if (sum_.size() != 0) {
    sum_ += " ";
  }
  sum_ += pair.second;
}

std::string fesenko::getSum() const
{
  return sum_;
}
