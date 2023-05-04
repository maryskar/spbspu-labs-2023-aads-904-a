#include "calc-verify.hpp"

bool turkin::verify::isADDerror(long long lhs, long long rhs) noexcept
{
  return lhs > 0 && rhs > 0 && (lhs + rhs < 0);
}

bool turkin::verify::isSUBerror(long long lhs, long long rhs) noexcept
{
  return lhs < 0 && rhs < 0 && (lhs + rhs > 0);
}

bool turkin::verify::isMULerror(long long lhs, long long rhs) noexcept
{
  if (lhs == 0 || lhs == 0)
  {
    return false;
  }	
  long long result = lhs * rhs;
  return !(lhs == result / rhs);
}

bool turkin::verify::isDIVerror(long long lhs, long long rhs) noexcept
{
  return lhs == 0 || rhs == 0;
}

bool turkin::verify::isMODerror(long long lhs, long long rhs) noexcept
{
  return isDIVerror(lhs, rhs);
}