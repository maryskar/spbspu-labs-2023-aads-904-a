#include "number.h"

#include <iomanip>

Number::Number(long long number):
  number(number)
{}
Number::Number(const Number& otherNumber):
  number(otherNumber.number)
{}
Number::Number(Number&& otherNumber) noexcept:
  number(otherNumber.number)
{}
char Number::getCondition() const
{
  return 1;
}
long long Number::getNumber()
{
  return number;
}
