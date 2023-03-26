#include "Operator.hpp"

#include <cmath>
#include <limits>
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

long long (*getOperatorFunction(char c))(long long, long long)
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

constexpr long long minLL = std::numeric_limits< long long >::min();
constexpr long long maxLL = std::numeric_limits< long long >::max();

long long odintsov::add(long long lhs, long long rhs)
{
  if (rhs > 0 && lhs > maxLL - rhs) {
    throw std::overflow_error("Addition overflow");
  }
  if (rhs < 0 && lhs < minLL - rhs) {
    throw std::underflow_error("Addition underflow");
  }
  return lhs + rhs;
}

long long odintsov::subtract(long long lhs, long long rhs)
{
  if (rhs < 0 && lhs > maxLL + rhs) {
    throw std::overflow_error("Subtraction overflow");
  }
  if (rhs > 0 && lhs < minLL + rhs) {
    throw std::underflow_error("Subtraction underflow");
  }
  return lhs - rhs;
}

long long odintsov::multiply(long long lhs, long long rhs)
{
  if ((rhs < 0 && lhs < maxLL / rhs) || (rhs > 0 && lhs > maxLL / rhs)) {
    throw std::overflow_error("Multiplication overflow");
  }
  if ((rhs > 0 && lhs < minLL / rhs) || (rhs < 0 && lhs > maxLL / rhs)) {
    throw std::underflow_error("Multiplication underflow");
  }
  return lhs * rhs;
}

long long odintsov::divide(long long lhs, long long rhs)
{
  if (rhs == 0) {
    throw std::invalid_argument("Division by 0");
  }
  if (rhs == -1 && lhs < maxLL * rhs) {
    throw std::overflow_error("Division overflow");
  }
  return lhs / rhs;
}

long long odintsov::modulo(long long lhs, long long rhs)
{
  long long res = lhs % rhs;
  if (res < 0) {
    res += rhs;
  }
  return res;
}
