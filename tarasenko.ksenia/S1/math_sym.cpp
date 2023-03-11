#include "math_sym.h"
#include <stdexcept>

tarasenko::MathSymbols::MathSymbols(char ms) :
  value_(ms)
{
  if (ms == '(')
  {
    priority_ = 0;
  }
  else if (ms == ')')
  {
    priority_ = 1;
  }
  else if (ms == '+' || ms == '-')
  {
    priority_ = 2;
  }
  else if (ms == '*' || ms == '/' || ms == '%')
  {
    priority_ = 3;
  }
  else
  {
    throw std::invalid_argument("Incorrect input");
  }
}

char tarasenko::MathSymbols::getValue() const
{
  return value_;
}

bool tarasenko::MathSymbols::operator<=(const MathSymbols& rhs) const
{
  return priority_ <= rhs.priority_;
}
