#include "partOfArithmeticExpression.h"
#include <algorithm>
#include <stdexcept>
namespace
{
  bool checkDigit(const std::string &str)
  {
    return str.find_first_not_of("0123456789") == std::string::npos;
  }
}
dimkashelk::PartOfArithmeticExpression::element::element(const std::string &str)
{
  if (checkDigit(str))
  {
    operand_ = std::stoll(str);
  }
  else
  {
    operator_ = str[0];
  }
}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(const std::string &str):
  isDigit(checkDigit(str)),
  element(str)
{}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(long long number):
  isDigit(true),
  element(number)
{}
bool dimkashelk::isGreaterPriority(const PartOfArithmeticExpression &lhs, const PartOfArithmeticExpression &rhs)
{
  if (lhs.isDigit || rhs.isDigit)
  {
    throw std::logic_error("Must be operator, not operand");
  }
  if (lhs.element.operator_ == '+' || lhs.element.operator_ == '-')
  {
    return rhs.element.operator_ == '*' || rhs.element.operator_ == '/' || rhs.element.operator_ == '%';
  }
  return false;
}
