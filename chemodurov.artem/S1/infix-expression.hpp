#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP

namespace chemodurov
{
  enum OPERATION
  {
    OPERATION_PLUS = '+',
    OPERATION_MINUS = '-',
    OPERATION_MULTIPLICATION = '*',
    OPERATION_DIVIDE = '/',
    OPERATION_REMINDER_OF_DIVISION = '%'
  };

  enum BRACE
  {
    BRACE_LEFT = '(',
    BRACE_RIGHT = ')'
  };

  struct InfixExpr
  {
    union OperationsOperandsBraces
    {
      int operand;
      OPERATION operation;
      BRACE brace;
    };
    bool isOperand;
    bool isOperation;
  };
}

#endif
