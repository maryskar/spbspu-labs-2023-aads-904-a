#include "elem.h"
#include <stdexcept>

tarasenko::Elem::Elem(long long digit):
  union_elem_{digit},
  is_number_(true)
{}

tarasenko::Elem::Elem(tarasenko::MathSymbols ms):
  union_elem_{0ll},
  is_number_(false)
{
  union_elem_.math_sym = MathSymbols(ms);
}
bool tarasenko::Elem::isNumber() const
{
  return is_number_;
}

long long tarasenko::Elem::getOperand() const
{
  if (is_number_)
  {
    return union_elem_.operand;
  }
  else
  {
    throw std::logic_error("It's not operand!");
  }
}

tarasenko::MathSymbols tarasenko::Elem::getOperation() const
{
  if (is_number_)
  {
    throw std::logic_error("It's not operation!");
  }
  else
  {
    return union_elem_.math_sym;
  }
}
