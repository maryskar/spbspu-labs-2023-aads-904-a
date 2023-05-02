#include "number.h"
#include <iomanip>

dmitriev::Number::Number(long long m_number):
  m_number(m_number)
{}
dmitriev::Number::Number(const Number& otherNumber):
  m_number(otherNumber.m_number)
{}
dmitriev::Number::Number(Number&& otherNumber) noexcept:
  m_number(otherNumber.m_number)
{}
char dmitriev::Number::getCondition() const
{
  return 1;
}
long long dmitriev::Number::getNumber() const
{
  return m_number;
}
