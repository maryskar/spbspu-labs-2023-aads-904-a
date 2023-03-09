#include "partOfArithmeticExpression.h"
#include <algorithm>
#include <stdexcept>
namespace
{
  bool checkDigit(const std::string &str)
  {
    return str.find_first_not_of("0123456789") == std::string::npos;
  }
  bool checkBracket(const std::string &str)
  {
    return str.find_first_not_of("()") == std::string::npos;
  }
}
dimkashelk::PartOfArithmeticExpression::element::element(const std::string &str)
{
  if (checkDigit(str))
  {
    operand_ = std::stoll(str);
  }
  else if (checkBracket(str))
  {
    bracket_ = str[0];
  }
  else
  {
    operator_ = str[0];
  }
}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(const std::string &str):
  isDigit(checkDigit(str)),
  isBracket(checkBracket(str)),
  element(str)
{}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(long long number):
  isDigit(true),
  isBracket(false),
  element(number)
{}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(const PartOfArithmeticExpression &part):
  isDigit(part.isDigit),
  isBracket(part.isBracket),
  element(part.element)
{}
dimkashelk::PartOfArithmeticExpression::PartOfArithmeticExpression(PartOfArithmeticExpression &&part):
  isDigit(part.isDigit),
  isBracket(part.isBracket),
  element(part.element)
{}
dimkashelk::PartOfArithmeticExpression &dimkashelk::PartOfArithmeticExpression::operator=(const PartOfArithmeticExpression &part)
{
  isDigit = part.isDigit;
  isBracket = part.isBracket;
  element = part.element;
  return *this;
}
bool dimkashelk::isGreaterPriority(const PartOfArithmeticExpression &lhs, const PartOfArithmeticExpression &rhs)
{
  if (lhs.isDigit || rhs.isDigit || lhs.isBracket || rhs.isBracket)
  {
    throw std::logic_error("Must be operator, not operand or brackets");
  }
  if (lhs.element.operator_ == '+' || lhs.element.operator_ == '-')
  {
    return rhs.element.operator_ == '*' || rhs.element.operator_ == '/' || rhs.element.operator_ == '%';
  }
  return false;
}
