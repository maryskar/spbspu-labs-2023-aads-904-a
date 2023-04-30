#include "mathExpression.h"
#include <iomanip>

bool Expression::isNumber() const
{
  return getCondition() == 1;
}

bool Expression::isOperator() const
{
  return getCondition() == 2;
}

bool Expression::isParenthesis() const
{
  return getCondition() == 3;
}

long long Expression::getNumber()
{
  throw std::logic_error("logic_error");
}

long long Expression::operator()(long long, long long)
{
  throw std::logic_error("logic_error");
}

bool Expression::operator==(Expression* otherExpr)
{
  return getPriority() == otherExpr->getPriority();
}

bool Expression::operator!=(Expression* otherExpr)
{
  return !operator==(otherExpr);
}

bool Expression::operator>(Expression* otherExpr)
{
  return getPriority() > otherExpr->getPriority();
}

bool Expression::operator<(Expression* otherExpr)
{
  return getPriority() < otherExpr->getPriority();
}

bool Expression::operator>=(Expression* otherExpr)
{
  return getPriority() >= otherExpr->getPriority();
}

bool Expression::operator<=(Expression* otherExpr)
{
  return getPriority() <= otherExpr->getPriority();
}

bool Expression::isOpenParenthesis()
{
  throw std::logic_error("logic_error");
}

bool Expression::isCloseParenthesis()
{
  throw std::logic_error("logic_error");
}

char Expression::getPriority() const
{
  throw std::logic_error("logic_error");
}
