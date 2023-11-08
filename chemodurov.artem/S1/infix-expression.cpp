#include "infix-expression.hpp"
#include <stdexcept>
#include "operation-and-parenthesis.hpp"

bool chemodurov::InfixExpr::isOperation() const noexcept
{
  return isOperation_;
}
bool chemodurov::InfixExpr::isOperand() const noexcept
{
  return isOperand_;
}
bool chemodurov::InfixExpr::isParenthesis() const noexcept
{
  return (!isOperand_ && !isOperation_);
}
chemodurov::operation_t chemodurov::InfixExpr::getOperation() const
{
  if (!isOperation_)
  {
    throw std::logic_error("It's not the operation");
  }
  return data_.operation_;
}
long chemodurov::InfixExpr::getOperand() const
{
  if (!isOperand_)
  {
    throw std::logic_error("It's not the operand");
  }
  return data_.operand_;
}
chemodurov::parenthesis_t chemodurov::InfixExpr::getParenthesis() const
{
  if (isOperand_ || isOperation_)
  {
    throw std::logic_error("It's not the brace");
  }
  return data_.parenthesis_;
}
chemodurov::InfixExpr::InfixExpr(operation_t operation):
 data_(operation),
 isOperand_(false),
 isOperation_(true)
{}
chemodurov::InfixExpr::InfixExpr(long operand):
 data_(operand),
 isOperand_(true),
 isOperation_(false)
{}
chemodurov::InfixExpr::InfixExpr(parenthesis_t parenthesis):
 data_(parenthesis),
 isOperand_(false),
 isOperation_(false)
{}

