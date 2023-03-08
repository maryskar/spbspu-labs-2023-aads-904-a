#include "elem.h"
#include <stdexcept>

tarasenko::Elem::Elem(long long digit):
  union_elem{digit},
  is_int(true)
{}

tarasenko::Elem::Elem(tarasenko::Operation op):
  union_elem{0ll},
  is_int(false)
{
  union_elem.operation = Operation(op);
}
bool tarasenko::Elem::isDigit() const
{
  return is_int;
}

long long tarasenko::Elem::getOperand() const
{
  if (is_int)
  {
    return union_elem.operand;
  }
  else
  {
    throw std::logic_error("It's not operand!");
  }
}

tarasenko::Operation tarasenko::Elem::getOperation() const
{
  if (is_int)
  {
    throw std::logic_error("It's not operation!");
  }
  else
  {
    return union_elem.operation;
  }
}
