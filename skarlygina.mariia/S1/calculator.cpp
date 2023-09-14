#include "calculator.h"
#include <limits>
#include <cmath>
#include <stdexcept>

constexpr long long limit_min = std::numeric_limits< long long >::min();
constexpr long long limit_max = std::numeric_limits< long long >::max();

long long skarlygina::sum(long long a, long long b)
{
  if (limit_max - a < b)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a + b;
}

long long skarlygina::substraction(long long a, long long b)
{
  if (limit_min + b > a)
  {
    throw std::overflow_error("Overflow numbers");
  }
  return a - b;
}

long long skarlygina::multiplication(long long a, long long b)
{
  if ((b > 0 && a > limit_max / b) || (b < 0 && a < limit_min / b))
  {
    throw std::overflow_error("Multiplication overflow");
  }
  return a * b;
}

long long skarlygina::division(long long a, long long b)
{
  if (b == 0)
  {
    throw std::invalid_argument("Division by zero");
  }
  if ((b > 0 && a > limit_max / b) || (b < 0 && a < limit_min / b))
  {
    throw std::overflow_error("Division overflow");
  }
  return a / b;
}

long long skarlygina::remainder(long long a, long long b)
{
  if (b == 0)
  {
    throw std::invalid_argument("Division by zero");
  }
  if (a == limit_min && b == -1)
  {
    throw std::overflow_error("Modulo overflow");
  }
  return a % b;
}

bool skarlygina::isOperation(char op)
{
  return (op == '+') || (op == '-') || (op == '*') || (op == '/') || (op == '%');
}

bool skarlygina::isGreaterPriority(char op1, char op2)
{
  return (op1 == '+' || op1 == '-') && (op2 == '%' || op2 == '*' || op2 == '/');
}

bool skarlygina::checkString(const std::string& op)
{
  if (op.length() == 1)
  {
    return isOperation(op[0]);
  }
  return false;
}
