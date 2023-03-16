#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP

namespace chemodurov
{
  enum Operation
  {
    OPERATION_PLUS = '+',
    OPERATION_MINUS = '-',
    OPERATION_MULTIPLICATION = '*',
    OPERATION_DIVIDE = '/',
    OPERATION_REMINDER_OF_DIVISION = '%'
  };

  enum Brace
  {
    BRACE_LEFT = '(',
    BRACE_RIGHT = ')'
  };

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
