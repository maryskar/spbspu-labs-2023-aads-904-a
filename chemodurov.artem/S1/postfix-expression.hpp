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

  class PostfixExpr
  {
   public:
    explicit PostfixExpr(Operation op);
    explicit PostfixExpr(long operand);
    bool isOperation() const noexcept;
    bool isOperand() const noexcept;
    Operation getOperation() const;
    long getOperand() const;
   private:
    OperationOperand data_;
    bool isOperand_;
  };
}

#endif
