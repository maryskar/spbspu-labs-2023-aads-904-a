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
    element_(parenthesis)
  {}
  ExpressionMember::ExpressionMember(operation_t operation):
    isOperand_(false),
    isParthenesis_(false),
    element_(operation)
  {}
  ExpressionMember::ExpressionMember(long long operand):
    isOperand_(true),
    isParthenesis_(false),
    element_(operand)
  {}

  ExpressionMember::ExpressionMember(const ExpressionMember &data):
    isOperand_(data.isOperand_),
    isParthenesis_(data.isParthenesis_),
    element_(data.element_)
  {}
  ExpressionMember::ExpressionMember(ExpressionMember && data):
    isOperand_(data.isOperand_),
    isParthenesis_(data.isParthenesis_),
    element_(data.element_)
  {}
  ExpressionMember &ExpressionMember::operator=(const ExpressionMember &data)
  {
    isOperand_ = data.isOperand_;
    isParthenesis_ = data.isParthenesis_;
    element_ = data.element_;
    return *this;
  }
  ExpressionMember &ExpressionMember::operator=(ExpressionMember &&data)
  {
    isOperand_ = data.isOperand_;
    isParthenesis_ = data.isParthenesis_;
    element_ = data.element_;
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
    return element_.operation_;
  }
  parenthesis_t ExpressionMember::getParenthesis() const
  {
    return element_.parenthesis_;
  }
  long long ExpressionMember::getOperand() const
  {
    return element_.operand_;
  }
  
}
