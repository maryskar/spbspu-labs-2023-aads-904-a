#include "Operator.hpp"

#include <cmath>
#include <stdexcept>

unsigned short getOperatorPriority(char c)
{
  if (c == '+' || c == '-') {
    return 1;
  }
  if (c == '*' || c == '/' || c == '%') {
    return 2;
  }
  return 0;
}

double (*getOperatorFunction(char c))(double, double)
{
  switch (c) {
  case '+':
    return &odintsov::add;
  case '-':
    return &odintsov::subtract;
  case '*':
    return &odintsov::multiply;
  case '/':
    return &odintsov::divide;
  case '%':
    return &odintsov::modulo;
  default:
    throw std::invalid_argument("Undefined operator");
  }
}

odintsov::Operator::Operator(char c):
  exec(getOperatorFunction(c)),
  priority_(getOperatorPriority(c))
{}

bool odintsov::Operator::operator>=(odintsov::Operator& rhs) const
{
  return priority_ >= rhs.priority_;
}

double odintsov::add(double lhs, double rhs)
{
  return lhs + rhs;
}

double odintsov::subtract(double lhs, double rhs)
{
  return lhs - rhs;
}

double odintsov::multiply(double lhs, double rhs)
{
  return lhs * rhs;
}

double odintsov::divide(double lhs, double rhs)
{
  return lhs / rhs;
}

double odintsov::modulo(double lhs, double rhs)
{
  return std::fmod(lhs, rhs);
}
