#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP
#include "operation-and-parenthesis.hpp"

namespace chemodurov
{
  class InfixExpr
  {
   public:
    explicit InfixExpr(operation_t op);
    explicit InfixExpr(long operand);
    explicit InfixExpr(parenthesis_t parenthesis);
    bool isOperation() const noexcept;
    bool isOperand() const noexcept;
    bool isParenthesis() const noexcept;
    operation_t getOperation() const;
    long getOperand() const;
    parenthesis_t getParenthesis() const;
   private:
    union OperationsOperandsParenthesis
    {
      long operand_;
      operation_t operation_;
      parenthesis_t parenthesis_;
      OperationsOperandsParenthesis(long operand): operand_(operand) {};
      OperationsOperandsParenthesis(operation_t operation): operation_(operation) {};
      OperationsOperandsParenthesis(parenthesis_t parenthesis): parenthesis_(parenthesis) {};
    } data_;
    bool isOperand_;
    bool isOperation_;
  };
}

#endif
