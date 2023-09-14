#include "calculator.h"
#include <limits>
#include <cmath>
#include <stdexcept>

constexpr long long limit_min = std::numeric_limits< long long >::min();
constexpr long long limit_max = std::numeric_limits< long long >::max();

long long skarlygina::sum(long long a, long long b)
{
  if (a < 0 && b < 0)
  {
    if (a < limit_min - b)
    {
      throw std::overflow_error("Overflow");
    }
  }
  if (a >= 0 && b > 0)
  {
    if (limit_max - a < b)
    {
      throw std::overflow_error("Overflow");
    }
  }
  return a + b;
}

long long skarlygina::substraction(long long a, long long b)
{
  if ((b < limit_min + a && a > 0) || (b > limit_max + a && a < 0))
  {
    throw std::overflow_error("Overflow");
  }
  return b - a;
}

long long skarlygina::multiplication(long long a, long long b)
{
  if ((a > 0 && b > 0) || (a < 0 && b < 0))
  {
    if (a > limit_max / b)
    {
      throw std::overflow_error("Overflow");
    }
  }
  else
  {
    if (a < 0 && b > 0)
    {
      if (a < limit_min / b)
      {
        throw std::overflow_error("Overflow");
      }
    }
    if (a > 0 && b < 0)
    {
      if (b < limit_min / a)
      {
        throw std::overflow_error("Overflow");
      }
    }
  }
  return a * b;
}

long long skarlygina::division(long long a, long long b)
{
  if (a == 0)
  {
    throw std::overflow_error("div by 0");
  }
  return b / a;
}

long long skarlygina::remainder(long long a, long long b)
{
  if (b > 0)
  {
    return b % a;
  }
  else
  {
    return (b + a * (std::abs(b) / a + 1));
  }
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
