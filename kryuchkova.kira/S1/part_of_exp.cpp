#include "part_of_exp.h"

namespace kryuchkova
{
  ExpressionMember::element::element(long long operand):
    operand_(operand)
  {}
  ExpressionMember::element::element(operation_t operation):
    operation_(operation)
  {}
  ExpressionMember::element::element(parenthesis_t parenthesis):
    parenthesis_(parenthesis)
  {}

  ExpressionMember::ExpressionMember(parenthesis_t parenthesis):
    isOperand_(false),
    isParthenesis_(true),
    element(parenthesis)
  {}
  ExpressionMember::ExpressionMember(operation_t operation):
    isOperand_(false),
    isParthenesis_(false),
    element(operation)
  {}
  ExpressionMember::ExpressionMember(long long operand):
    isOperand_(true),
    isParthenesis_(false),
    element(operand)
  {}

  ExpressionMember::ExpressionMember(const ExpressionMember &data):
    isOperand_(data.isOperand_),
    isParthenesis_(data.isParthenesis_),
    element(data.element)
  {}
  ExpressionMember::ExpressionMember(ExpressionMember && data):
    isOperand_(data.isOperand_),
    isParthenesis_(data.isParthenesis_),
    element(data.element)
  {}
  ExpressionMember &ExpressionMember::operator=(const ExpressionMember &data)
  {
    isOperand_ = data.isOperand_;
    isParthenesis_ = data.isParthenesis_;
    element = data.element;
    return *this;
  }
  ExpressionMember &ExpressionMember::operator=(ExpressionMember &&data)
  {
    isOperand_ = data.isOperand_;
    isParthenesis_ = data.isParthenesis_;
    element = data.element;
    return *this;
  }

  bool ExpressionMember::isOperand() const
  {
    return isOperand_;
  }
  bool ExpressionMember::isParenthesis() const
  {
    return isParthenesis_;
  }
  operation_t ExpressionMember::getOperation() const
  {
    return element.operation_;
  }
  parenthesis_t ExpressionMember::getParenthesis() const
  {
    return element.parenthesis_;
  }
  long long ExpressionMember::getOperand() const
  {
    return element.operand_;
  }

  bool cmpPriority(const operation_t &lhs, const operation_t &rhs)
  {
    if (lhs == operation_t::SUBTRACTION || lhs == operation_t::ADDITION)
    {
      return rhs == operation_t::MULTIPLICATION || rhs == operation_t::DIVISION || rhs == operation_t::EUCLIDEAN_DIVISION;
    }
    return false;
  }
}
