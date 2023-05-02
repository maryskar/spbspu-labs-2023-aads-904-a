#include "mathExpression.h"
#include <stdexcept>

bool dmitriev::Expression::isNumber() const
{
  return getCondition() == 1;
}

bool dmitriev::Expression::isOperator() const
{
  return getCondition() == 2;
}

bool dmitriev::Expression::isParenthesis() const
{
  return getCondition() == 3;
}

long long dmitriev::Expression::getNumber() const
{
  throw std::logic_error("logic_error");
}

long long dmitriev::Expression::operator()(long long, long long)
{
  throw std::logic_error("logic_error");
}

bool dmitriev::Expression::operator==(Expression* otherExpr)
{
  return getPriority() == otherExpr->getPriority();
}

bool dmitriev::Expression::operator!=(Expression* otherExpr)
{
  return !operator==(otherExpr);
}

bool dmitriev::Expression::operator>(Expression* otherExpr)
{
  return getPriority() > otherExpr->getPriority();
}

bool dmitriev::Expression::operator<(Expression* otherExpr)
{
  return getPriority() < otherExpr->getPriority();
}

bool dmitriev::Expression::operator>=(Expression* otherExpr)
{
  return getPriority() >= otherExpr->getPriority();
}

bool dmitriev::Expression::operator<=(Expression* otherExpr)
{
  return getPriority() <= otherExpr->getPriority();
}

bool dmitriev::Expression::isOpenParenthesis() const
{
  throw std::logic_error("logic_error");
}

bool dmitriev::Expression::isCloseParenthesis() const
{
  throw std::logic_error("logic_error");
}

char dmitriev::Expression::getPriority() const
{
  throw std::logic_error("logic_error");
}
