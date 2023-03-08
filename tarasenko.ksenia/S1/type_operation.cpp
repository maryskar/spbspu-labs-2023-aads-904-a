#include "type_operation.h"
#include <stdexcept>

tarasenko::Operation::Operation(char op) :
  value_(op)
{
  if (op == '(')
  {
    priority_ = 0;
  }
  else if (op == ')')
  {
    priority_ = 1;
  }
  else if (op == '+' || op == '-')
  {
    priority_ = 2;
  }
  else if (op == '*' || op == '/' || op == '%')
  {
    priority_ = 3;
  }
  else
  {
    throw std::invalid_argument("Incorrect input");
  }
}

char tarasenko::Operation::getValue() const
{
  return value_;
}

bool tarasenko::Operation::operator<=(const Operation& rhs) const
{
  return priority_ <= rhs.priority_;
}
