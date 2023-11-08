#include "func-objects.hpp"

#include <stdexcept>

#include <calc-verify.hpp>

turkin::KeySum::KeySum():
  sum_(0)
{}

namespace
{
  void llsum_check(long long lhs, long long rhs)
  {
    if (turkin::isADDerror(lhs, rhs) || turkin::isSUBerror(lhs, rhs) || turkin::isADDerror(rhs, lhs) || turkin::isSUBerror(rhs, lhs))
    {
      throw std::overflow_error("num add error");
    }
  }
}

void turkin::KeySum::operator()(const std::pair< long long, std::string > & pair)
{
  llsum_check(sum_, pair.first);
  sum_ += pair.first;
}

long long turkin::KeySum::get() const
{
  return sum_;
}

turkin::StrSum::StrSum():
  sum_("")
{}

void turkin::StrSum::operator()(const std::pair< long long, std::string > & pair)
{
  if (sum_.max_size() - sum_.size() < pair.second.size())
  {
    throw std::overflow_error("string add error");
  }
  sum_ += " " + pair.second;
}

std::string turkin::StrSum::get() const
{
  return sum_;
}
