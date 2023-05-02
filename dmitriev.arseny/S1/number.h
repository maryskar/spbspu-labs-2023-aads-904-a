#ifndef NUMBER_H
#define NUMBER_H

#include "mathExpression.h"

namespace dmitriev
{
  class Number : public Expression
  {
  public:
    explicit Number(long long m_number);
    Number(const Number& otherNumber);
    Number(Number&& otherNumber) noexcept;

    char getCondition() const override;
    long long getNumber() const override;

  private:
    long long m_number;

  };
}

#endif
