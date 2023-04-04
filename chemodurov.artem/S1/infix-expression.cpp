#include "infix-expression.hpp"
#include <stdexcept>
#include "operation-and-brace.hpp"

bool chemodurov::InfixExpr::isOperation() const noexcept
{
  return isOperation_;
}
bool chemodurov::InfixExpr::isOperand() const noexcept
{
  return isOperand_;
}
bool chemodurov::InfixExpr::isBrace() const noexcept
{
  return (!isOperand_ && !isOperation_);
}
chemodurov::Operation chemodurov::InfixExpr::getOperation() const
{
  if (!isOperation_)
  {
    throw std::logic_error("It's not the operation");
  }
  return data_.operation;
}
long chemodurov::InfixExpr::getOperand() const
{
  if (!isOperand_)
  {
    throw std::logic_error("It's not the operand");
  }
  return data_.operand;
}
chemodurov::Brace chemodurov::InfixExpr::getBrace() const
{
  if (isOperand_ || isOperation_)
  {
    throw std::logic_error("It's not the brace");
  }
  return data_.brace;
}
chemodurov::InfixExpr::InfixExpr(chemodurov::Operation op):
 data_({op}),
 isOperand_(false),
 isOperation_(true)
{}
chemodurov::InfixExpr::InfixExpr(long operand):
 data_({operand}),
 isOperand_(true),
 isOperation_(false)
{}
chemodurov::InfixExpr::InfixExpr(chemodurov::Brace brace):
 data_({brace}),
 isOperand_(false),
 isOperation_(false)
{}
