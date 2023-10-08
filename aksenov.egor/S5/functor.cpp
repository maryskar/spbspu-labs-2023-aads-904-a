#include "functor.h"
#include <iostream>
#include <stdexcept>
#include <checkOverflow.h>

aksenov::Summator::Summator():
  res_(0),
  finalStr_(0)
{}

void aksenov::Summator::operator()(const std::pair< long long, std::string > &pair)
{
  if (aksenov::isOverflow(res_, pair.first, '+'))
  {
    throw std::logic_error("overflow");
  }
  res_ += pair.first;
}

std::ostream &aksenov::operator<<(std::ostream &out, const aksenov::Summator &func)
{
  out << func.res_ << func.finalStr_ << "\n";
  return out;
}