#include "elem.h"
#include <stdexcept>

tarasenko::Elem::Elem(long long digit)
{
  union_elem.operand = digit;
  is_int = true;
}

tarasenko::Elem::Elem(char op)
{
  union_elem.operation = op;
  is_int = false;
}
bool tarasenko::Elem::isDigit() const
{
  return is_int;
}

long long tarasenko::Elem::getValueOfOperand() const
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

char tarasenko::Elem::getValueOfOperation() const
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
