#ifndef POSTFIX_EXPR_HPP
#define POSTFIX_EXPR_HPP
#include "operation-and-brace.hpp"

namespace chemodurov
{
  union OperationOperand
  {
    int operand;
    Operation operation;
  };

  struct PostfixExpr
  {
    OperationOperand data;
    bool isOperand;
  };
}

#endif
