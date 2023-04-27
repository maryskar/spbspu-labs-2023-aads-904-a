#include "partOfArithmeticExpression.h"
dimkashelk::PartOfArithExpr::element::element(long long o):
  operand_(o)
{}
dimkashelk::PartOfArithExpr::element::element(Operator oper):
  operator_(oper)
{}
dimkashelk::PartOfArithExpr::element::element(Parenthesis parenthesis):
  parenthesis_(parenthesis)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(Parenthesis parenthesis):
  isNumber_(false),
  isParenthesis_(true),
  element(parenthesis)
{}
dimkashelk::PartOfArithExpr::PartOfArithExpr(Operator oper):
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
dimkashelk::PartOfArithExpr &dimkashelk::PartOfArithExpr::operator=(PartOfArithExpr &&part)
{
  isNumber_ = part.isNumber_;
  isParenthesis_ = part.isParenthesis_;
  element = part.element;
  return *this;
}
bool dimkashelk::PartOfArithExpr::isNumber() const
{
  return isNumber_;
}
bool dimkashelk::PartOfArithExpr::isParenthesis() const
{
  return isParenthesis_;
}
dimkashelk::Operator dimkashelk::PartOfArithExpr::getOperator() const
{
  return element.operator_;
}
dimkashelk::Parenthesis dimkashelk::PartOfArithExpr::getParenthesis() const
{
  return element.parenthesis_;
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
