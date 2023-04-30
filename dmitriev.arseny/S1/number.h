#ifndef NUMBER_H
#define NUMBER_H

#include "mathExpression.h"

class Number : public Expression
{
public:
  explicit Number(long long number);
  Number(const Number& otherNumber);
  Number(Number&& otherNumber) noexcept;

  char getCondition() override;
  long long getNumber() override;

private:
  long long number;

};

#endif
