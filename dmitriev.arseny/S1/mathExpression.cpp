#include "mathExpression.h"

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
