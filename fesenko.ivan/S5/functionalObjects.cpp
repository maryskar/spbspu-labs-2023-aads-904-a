#include "functionalObjects.h"
#include <stdexcept>
#include <limits>

fesenko::Summator::Summator():
  llSum_(0),
  strSum_("")
{}

void fesenko::Summator::operator()(const std::pair< long long, std::string > &value_type)
{
  if (llSum_ > 0 && value_type.first > 0 && llSum_ > std::numeric_limits< long long >::max() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  if (llSum_ < 0 && value_type.first < 0 && llSum_ < std::numeric_limits< long long >::min() - value_type.first) {
    throw std::overflow_error("Overflow");
  }
  llSum_ += value_type.first;

  if (strSum_.max_size() - strSum_.size() < value_type.second.size()) {
    throw std::overflow_error("Overflow");
  }
  if (strSum_.size() != 0) {
    strSum_ += " ";
  }
  strSum_ += value_type.second;
}

std::pair< long long, std::string > fesenko::Summator::getSum() const
{
  return std::make_pair(llSum_, strSum_);
}
