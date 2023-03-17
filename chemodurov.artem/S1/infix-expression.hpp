#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP
#include "operation-and-brace.hpp"

namespace chemodurov
{
  union OperationsOperandsBraces
  {
    int operand;
    Operation operation;
    Brace brace;
  };

  struct InfixExpr
  {
    OperationsOperandsBraces data;
    bool isOperand;
    bool isOperation;
  };
}

#endif
