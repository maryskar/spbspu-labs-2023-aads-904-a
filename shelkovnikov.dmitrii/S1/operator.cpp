#include "operator.h"
#include <stdexcept>
dimkashelk::Operator::Operator(const char str):
  operator_(str)
{
  if (!isOperator())
  {
    throw std::logic_error("It's not a operator");
  }
}
bool dimkashelk::Operator::isAdd()
{
  return operator_ == '+';
}
bool dimkashelk::Operator::isSubtraction()
{
  return operator_ == '-';
}
bool dimkashelk::Operator::isMultiplication()
{
  return operator_ == '*';
}
bool dimkashelk::Operator::isDivision()
{
  return operator_ == '/';
}
bool dimkashelk::Operator::isRemainder()
{
  return operator_ == '%';
}
bool dimkashelk::Operator::isOperator()
{
  return isAdd() || isSubtraction() || isMultiplication() || isDivision() || isRemainder();
}
