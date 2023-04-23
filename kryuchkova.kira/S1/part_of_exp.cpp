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

  
  
}
