#ifndef OPERATOR_H
#define OPERATOR_H

#include "mathExpression.h"

class Operator: public Expression
{
public:
  explicit Operator(char op);
  Operator(const Operator& otherOperator);
  Operator(Operator&& otherOperator) noexcept;

  char getCondition() const override;
  char getPriority() const override;
  long long operator()(long long, long long) override;

private:
  long long (*mathOperator)(long long, long long);
  char priority;

};

#endif
