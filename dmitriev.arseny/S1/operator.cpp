#include "operator.h"

#include <iomanip>
#include <limits>

const long long min = std::numeric_limits< long long >::min();
const long long max = std::numeric_limits< long long >::max();

long long plus(long long p1, long long p2);
long long minus(long long p1, long long p2);
long long multiple(long long p1, long long p2);
long long division(long long p1, long long p2);
long long mod(long long p1, long long p2);

char definePriority(char op);
auto defineOperator(char op)
{
  if (op == '+')
  {
    return plus;
  }
  else if (op == '-')
  {
    return minus;
  }
  else if (op == '*')
  {
    return multiple;
  }
  else if (op == '/')
  {
    return division;
  }
  else if (op == '%')
  {
    return mod;
  }
  else
  {
    throw std::logic_error("unknown operator");
  }
}


Operator::Operator(char op):
  mathOperator(defineOperator(op)),
  priority(definePriority(op))
{}

Operator::Operator(const Operator& otherOperator):
  mathOperator(otherOperator.mathOperator),
  priority(otherOperator.priority)
{}

Operator::Operator(Operator&& otherOperator) noexcept:
  mathOperator(otherOperator.mathOperator),
  priority(otherOperator.priority)
{}

char Operator::getCondition()
{
  return 2;
}
long long Operator::getNumber()
{
  throw std::logic_error("logic_error");
}
long long Operator::getOper(long long p1, long long p2)
{
  return mathOperator(p1, p2);
}
bool Operator::isOpenParenthesis()
{
  throw std::logic_error("logic_error");
}
bool Operator::isCloseParenthesis()
{
  throw std::logic_error("logic_error");
}
char Operator::getPriority()
{
  return priority;
}

char definePriority(char op)
{
  char priority = 0;
  if ((op == '+') || (op == '-'))
  {
    priority = 1;
  }
  else if (op == '%')
  {
    priority = 2;
  }
  else if ((op == '*') || (op == '/'))
  {
    priority = 3;
  }

  return priority;
}

long long plus(long long p1, long long p2)
{
  if (p1 > max - p2 && p2 > 0)
  {
    throw std::overflow_error("overflow_error");
  }
  if (p1 < min - p2 && p2 < 0)
  {
    throw std::underflow_error("underflow_error");
  }

  return p2 + p1;
}

long long minus(long long p1, long long p2)
{
  if (p2 > max + p1 && p1 < 0)
  {
    throw std::overflow_error("overflow_error");
  }
  if (p2 < min + p1 && p1 > 0)
  {
    throw std::underflow_error("underflow_error");
  }

  return p2 - p1;
}

long long multiple(long long p1, long long p2)
{
  if (p2 == 0)
  {
    return 0;
  }
  else if (max / std::abs(p2) < std::abs(p1))
  {
    throw std::overflow_error("overflow error");
  }

  return p2 * p1;
}

long long division(long long p1, long long p2)
{
  if (p1 == 0)
  {
    throw std::logic_error("div on zero");
  }

  return p2 / p1;
}

long long mod(long long p1, long long p2)
{
  if (p1 == 0)
  {
    throw std::logic_error("mod on zero");
  }
  if ((p2 % p1) < 0)
  {
    return (p2 % p1) + p1;
  }
  return p2 % p1;
}
