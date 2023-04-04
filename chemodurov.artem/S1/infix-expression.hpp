#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP
#include "operation-and-brace.hpp"

namespace chemodurov
{
  union OperationsOperandsBraces
  {
    long operand;
    Operation operation;
    Brace brace;
  };

  class InfixExpr
  {
   public:
    explicit InfixExpr(Operation op);
    explicit InfixExpr(long operand);
    explicit InfixExpr(Brace brace);
    bool isOperation() const noexcept;
    bool isOperand() const noexcept;
    bool isBrace() const noexcept;
    Operation getOperation() const;
    long getOperand() const;
    Brace getBrace() const;
   private:
    OperationsOperandsBraces data_;
    bool isOperand_;
    bool isOperation_;
  };
}

#endif
