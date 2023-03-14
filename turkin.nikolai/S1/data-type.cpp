#include "data-type.h"
#include <stdexcept>

calc_t::operator long long() const
{
  if (!isgigit)
  {
    throw std::runtime_error("isnt digit");
  }
  return calc.num;
}

calc_t::operator char() const
{
  if (isgigit)
  {
    throw std::runtime_error("isnt char");
  }
  return calc.sign;
}

calc_t calc_t::operator=(long long num)
{
  calc.num = num;
  isgigit = true;
  return * this;
}

calc_t calc_t::operator=(char sign)
{
  calc.sign = sign;
  isgigit = false;
  return * this;
}

bool calc_t::operator==(long long num)
{
  if (!isgigit)
  {
    throw std::runtime_error("isnt digit");
  }
  return calc.num == num;
}

bool calc_t::operator==(char sign)
{
  if (isgigit)
  {
    throw std::runtime_error("isnt char");
  }
  return calc.sign == sign;
}

bool calc_t::operator!=(long long num)
{
  if (!isgigit)
  {
    throw std::runtime_error("isnt digit");
  }
  return calc.num != num;
}

bool calc_t::operator!=(char sign)
{
  if (isgigit)
  {
    throw std::runtime_error("isnt char");
  }
  return calc.sign != sign;
}
