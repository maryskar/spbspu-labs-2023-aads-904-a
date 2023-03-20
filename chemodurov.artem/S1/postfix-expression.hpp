#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP
#include "operation-and-brace.hpp"

namespace chemodurov
{
  union OperationOperand
  {
    long operand;
    Operation operation;
  };

  struct PostfixExpr
  {
    OperationOperand data;
    bool isOperand;
  };
}

#endif
