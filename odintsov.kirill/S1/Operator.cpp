#include "Operator.hpp"

#include <limits>
#include <stdexcept>

namespace {
  constexpr long long minLL = std::numeric_limits< long long >::min();
  constexpr long long maxLL = std::numeric_limits< long long >::max();

  long long add(long long lhs, long long rhs)
  {
    if (rhs > 0 && lhs > maxLL - rhs) {
      throw std::overflow_error("Addition overflow");
    }
    if (rhs < 0 && lhs < minLL - rhs) {
      throw std::underflow_error("Addition underflow");
    }
    return lhs + rhs;
  }

  long long subtract(long long lhs, long long rhs)
  {
    if (rhs < 0 && lhs > maxLL + rhs) {
      throw std::overflow_error("Subtraction overflow");
    }
    if (rhs > 0 && lhs < minLL + rhs) {
      throw std::underflow_error("Subtraction underflow");
    }
    return lhs - rhs;
  }

  long long multiply(long long lhs, long long rhs)
  {
    if ((rhs < 0 && lhs < maxLL / rhs) || (rhs > 0 && lhs > maxLL / rhs)) {
      throw std::overflow_error("Multiplication overflow");
    }
    if ((rhs > 0 && lhs < minLL / rhs) || (rhs < 0 && lhs > maxLL / rhs)) {
      throw std::underflow_error("Multiplication underflow");
    }
    return lhs * rhs;
  }

  long long divide(long long lhs, long long rhs)
  {
    if (rhs == 0) {
      throw std::invalid_argument("Division by 0");
    }
    if (rhs == -1 && lhs < maxLL * rhs) {
      throw std::overflow_error("Division overflow");
    }
    return lhs / rhs;
  }

  long long modulo(long long lhs, long long rhs)
  {
    if (rhs == 0) {
      throw std::invalid_argument("Attempt to get remainder of division by 0");
    }
    long long res = lhs % rhs;
    if (res < 0) {
      res += rhs;
    }
    return res;
  }

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

  using funcPtr = long long (*)(long long, long long);

  funcPtr getOperatorFunction(char c)
  {
    switch (c) {
    case '+':
      return add;
    case '-':
      return subtract;
    case '*':
      return multiply;
    case '/':
      return divide;
    case '%':
      return modulo;
    default:
      throw std::invalid_argument("Undefined operator");
    }
  }
}

odintsov::Operator::Operator(char c):
  exec_(getOperatorFunction(c)),
  priority_(getOperatorPriority(c))
{}

long long odintsov::Operator::exec(long long lhs, long long rhs) const
{
  return exec_(lhs, rhs);
}

bool odintsov::Operator::operator<(const Operator& rhs) const
{
  return priority_ < rhs.priority_;
}

bool odintsov::Operator::operator>(const Operator& rhs) const
{
  return rhs < *this;
}

bool odintsov::Operator::operator<=(const Operator& rhs) const
{
  return !(*this > rhs);
}

bool odintsov::Operator::operator>=(const Operator& rhs) const
{
  return !(*this < rhs);
}
