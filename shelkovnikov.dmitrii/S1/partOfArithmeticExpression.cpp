#include "partOfArithmeticExpression.h"
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
dimkashelk::PartOfArithExpr::element::element(long long o):
  operand_(o)
{}
dimkashelk::PartOfArithExpr::element::element(char o):
  operator_(o)
{}
dimkashelk::PartOfArithExpr::element::element(const std::string &str)
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
dimkashelk::PartOfArithExpr::PartOfArithExpr(const std::string &str):
  isDigit_(checkDigit(str)),
  isBracket(checkBracket(str)),
  element(str)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(long long number):
  isDigit_(true),
  isBracket(false),
  element(number)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(const PartOfArithExpr &part):
  isDigit_(part.isDigit_),
  isBracket(part.isBracket),
  element(part.element)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(PartOfArithExpr &&part):
  isDigit_(part.isDigit_),
  isBracket(part.isBracket),
  element(part.element)
{}
dimkashelk::PartOfArithExpr &dimkashelk::PartOfArithExpr::operator=(const PartOfArithExpr &part)
{
  isDigit_ = part.isDigit_;
  isBracket = part.isBracket;
  element = part.element;
  return *this;
}
dimkashelk::PartOfArithExpr &dimkashelk::PartOfArithExpr::operator=(dimkashelk::PartOfArithExpr &&part)
{
  isDigit_ = part.isDigit_;
  isBracket = part.isBracket;
  element = part.element;
  return *this;
}
bool dimkashelk::isGreaterPriority(const PartOfArithExpr &lhs, const PartOfArithExpr &rhs)
{
  if (lhs.isDigit_ || rhs.isDigit_ || lhs.isBracket || rhs.isBracket)
  {
    throw std::logic_error("Must be operator, not operand or brackets");
  }
  if (lhs.element.operator_ == '+' || lhs.element.operator_ == '-')
  {
    return rhs.element.operator_ == '*' || rhs.element.operator_ == '/' || rhs.element.operator_ == '%';
  }
  return false;
}
