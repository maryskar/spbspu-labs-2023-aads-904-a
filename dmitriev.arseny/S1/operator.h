#ifndef OPERATOR_H
#define OPERATOR_H

#include "mathExpression.h"

namespace dmitriev
{
  class Operator : public Expression
  {
  public:
    explicit Operator(char op);
    Operator(const Operator& otherOperator);
    Operator(Operator&& otherOperator) noexcept;

    char getCondition() const override;
    char getPriority() const override;
    long long operator()(long long, long long) override;

  private:
    long long (*m_mathOperator)(long long, long long);
    char m_priority;

  };
}

#endif
