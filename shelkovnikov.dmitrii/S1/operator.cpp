#include "operator.h"
#include <stdexcept>
dimkashelk::Operator::Operator(char c):
  operator_(c)
{
  if (!isOperator(c))
  {
    throw std::logic_error("It's not a operator");
  }
}
bool dimkashelk::Operator::isAdd() const
{
  return operator_ == '+';
}
bool dimkashelk::Operator::isSubtraction() const
{
  return operator_ == '-';
}
bool dimkashelk::Operator::isMultiplication() const
{
  return operator_ == '*';
}
bool dimkashelk::Operator::isDivision() const
{
  return operator_ == '/';
}
bool dimkashelk::Operator::isRemainder() const
{
  return operator_ == '%';
}
bool dimkashelk::Operator::isOperator(char c)
{
  std::string oper = "+-*/%";
  return oper.find_first_of(c) != std::string::npos;
}
