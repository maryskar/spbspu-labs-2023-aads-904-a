#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP
#include "operation-and-parenthesis.hpp"

namespace chemodurov
{
  class PostfixExpr
  {
   public:
    explicit PostfixExpr(operation_t op);
    explicit PostfixExpr(long operand);
    bool isOperation() const noexcept;
    bool isOperand() const noexcept;
    operation_t getOperation() const;
    long getOperand() const;
   private:
    union OperationOperand
    {
      long operand_;
      operation_t operation_;
      OperationOperand(long operand): operand_(operand) {};
      OperationOperand(operation_t operation): operation_(operation) {};
    } data_;
    bool isOperand_;
  };
}

#endif
