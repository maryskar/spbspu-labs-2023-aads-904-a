#ifndef PART_OF_EXP_H
#define PART_OF_EXP_H

#include "operations_parentheses.h"

namespace kryuchkova
{
  class ExpressionMember
  {
  public:
    explicit ExpressionMember(parenthesis_t parenthesis);
    explicit ExpressionMember(operation_t operation);
    explicit ExpressionMember(long long operand);
    ExpressionMember(const ExpressionMember &data);
    ExpressionMember(ExpressionMember &&data);
    ExpressionMember &operator=(const ExpressionMember &data);
    ExpressionMember &operator=(ExpressionMember &&data);
    bool isOperand() const;
    bool isParenthesis() const;
    long long getOperand() const;
    operation_t getOperation() const;
    parenthesis_t getParenthesis() const;
  private:
    union element
    {
      long long operand_;
      operation_t operation_;
      parenthesis_t parenthesis_;
      explicit element(long long operand);
      explicit element(operation_t operation);
      explicit element(parenthesis_t parenthesis);
    } element_;
    bool isOperand_;
    bool isParthenesis_;
  };
  bool CpmPriority(const operation_t &lhs, const operation_t &rhs);
}

#endif
