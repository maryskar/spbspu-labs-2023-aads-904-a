#include "mathExpression.h"
#include <iomanip>

bool Expression::isNumber()
{
  return getCondition() == 1;
}

bool Expression::isOperator()
{
  return getCondition() == 2;
}

bool Expression::isParenthesis()
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

bool Expression::isOpenParenthesis()
{
  throw std::logic_error("logic_error");
}

bool Expression::isCloseParenthesis()
{
  throw std::logic_error("logic_error");
}

char Expression::getPriority()
{
  throw std::logic_error("logic_error");
}
