#include "postfix-expression.hpp"
#include <stdexcept>
#include "operation-and-parenthesis.hpp"

chemodurov::PostfixExpr::PostfixExpr(operation_t op):
 data_(op),
 isOperand_(false)
{}

chemodurov::PostfixExpr::PostfixExpr(long operand):
 data_(operand),
 isOperand_(true)
{}

bool chemodurov::PostfixExpr::isOperation() const noexcept
{
  return !isOperand_;
}

bool chemodurov::PostfixExpr::isOperand() const noexcept
{
  return isOperand_;
}

chemodurov::operation_t chemodurov::PostfixExpr::getOperation() const
{
  if (isOperand_)
  {
    throw std::logic_error("It's not the operation");
  }
  return data_.operation_;
}

long chemodurov::PostfixExpr::getOperand() const
{
  if (!isOperand_)
  {
    throw std::logic_error("It's not the operand");
  }
  return data_.operand_;
}
