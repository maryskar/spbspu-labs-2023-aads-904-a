#include "expressionpart.h"
ExpPart::ExpPart(brackets_t br):
  isOperation_(false),
  isBracket_(true),
  isOperand_(false),
  content_{br}
{
}
ExpPart::ExpPart(operations_t op):
  isOperation_(true),
  isBracket_(false),
  isOperand_(false),
  content_{op}
{
}
ExpPart::ExpPart(long long op):
  isOperation_(false),
  isBracket_(false),
  isOperand_(true),
  content_{op}
{
}
bool ExpPart::isOperation() const
{
  return isOperation_;
}
bool ExpPart::isBracket() const
{
  return isBracket_;
}
bool ExpPart::isOperand() const
{
  return isOperand_;
}
operations_t ExpPart::getOperation() const
{
  if (isOperation_)
  {
    return content_.operation_;
  }
  throw;
}
long long ExpPart::getOperand() const
{
  if (isOperand_)
  {
    return content_.operand_;
  }
  throw;
}
brackets_t ExpPart::getBracket() const
{
  if (isBracket_)
  {
    return content_.bracket_;
  }
  throw;
}
