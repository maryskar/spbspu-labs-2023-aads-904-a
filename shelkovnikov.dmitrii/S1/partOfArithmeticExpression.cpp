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
    try
    {
      dimkashelk::Parenthesis bracket(str[0]);
      return true;
    }
    catch (...)
    {
      return false;
    }
  }
}
dimkashelk::PartOfArithExpr::element::element(long long o):
  operand_(o)
{}
dimkashelk::PartOfArithExpr::element::element(dimkashelk::Operator oper):
  operator_(oper)
{}
dimkashelk::PartOfArithExpr::element::element(dimkashelk::Parenthesis parenthesis):
  bracket_(parenthesis)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(dimkashelk::Parenthesis parenthesis):
  isNumber_(false),
  isParenthesis_(true),
  element(parenthesis)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(dimkashelk::Operator oper):
  isNumber_(false),
  isParenthesis_(false),
  element(oper)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(long long number):
  isNumber_(true),
  isParenthesis_(false),
  element(number)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(const PartOfArithExpr &part):
  isNumber_(part.isNumber_),
  isParenthesis_(part.isParenthesis_),
  element(part.element)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(PartOfArithExpr &&part):
  isNumber_(part.isNumber_),
  isParenthesis_(part.isParenthesis_),
  element(part.element)
{}
dimkashelk::PartOfArithExpr &dimkashelk::PartOfArithExpr::operator=(const PartOfArithExpr &part)
{
  isNumber_ = part.isNumber_;
  isParenthesis_ = part.isParenthesis_;
  element = part.element;
  return *this;
}
dimkashelk::PartOfArithExpr &dimkashelk::PartOfArithExpr::operator=(dimkashelk::PartOfArithExpr &&part)
{
  isNumber_ = part.isNumber_;
  isParenthesis_ = part.isParenthesis_;
  element = part.element;
  return *this;
}
bool dimkashelk::PartOfArithExpr::isDigit() const
{
  return isNumber_;
}
bool dimkashelk::PartOfArithExpr::isBracket() const
{
  return isParenthesis_;
}
dimkashelk::Operator dimkashelk::PartOfArithExpr::getOperator() const
{
  return element.operator_;
}
dimkashelk::Parenthesis dimkashelk::PartOfArithExpr::getBracket() const
{
  return element.bracket_;
}
long long dimkashelk::PartOfArithExpr::getOperand() const
{
  return element.operand_;
}
bool dimkashelk::isGreaterPriority(const Operator &lhs, const Operator &rhs)
{
  if (lhs.isAdd() || lhs.isSubtraction())
  {
    return rhs.isMultiplication() || rhs.isDivision() || rhs.isRemainder();
  }
  return false;
}
