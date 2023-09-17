#include "func-objects.hpp"

#include <stdexcept>

#include <calc-verify.hpp>

turkin::KeySum::KeySum():
  sum_(0)
{}

void turkin::KeySum::operator()(const std::pair< int, std::string > & pair)
{
  if (isADDerror(sum_, pair.first))
  {
    throw std::overflow_error("ADD error");
  }
  sum_ += pair.first;
}

int turkin::KeySum::get() const
{
  return sum_;
}

turkin::StrSum::StrSum():
  sum_("")
{}

void turkin::StrSum::operator()(const std::pair< int, std::string > & pair)
{
  sum_ += " " + pair.second;
}

std::string turkin::StrSum::get() const
{
  return sum_;
}
