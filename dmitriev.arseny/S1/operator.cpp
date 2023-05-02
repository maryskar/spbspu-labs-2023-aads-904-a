#include "operator.h"
#include <stdexcept>
#include <limits>

constexpr long long min = std::numeric_limits< long long >::min();
constexpr long long max = std::numeric_limits< long long >::max();

namespace
{
  char definePriority(char op)
  {
    char m_priority = 0;
    if ((op == '+') || (op == '-'))
    {
      m_priority = 1;
    }
    else if (op == '%')
    {
      m_priority = 2;
    }
    else if ((op == '*') || (op == '/'))
    {
      m_priority = 3;
    }

    return m_priority;
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
}

dmitriev::Operator::Operator(char op):
  m_mathOperator(defineOperator(op)),
  m_priority(definePriority(op))
{}

dmitriev::Operator::Operator(const Operator& otherOperator):
  m_mathOperator(otherOperator.m_mathOperator),
  m_priority(otherOperator.m_priority)
{}

dmitriev::Operator::Operator(Operator&& otherOperator) noexcept:
  m_mathOperator(otherOperator.m_mathOperator),
  m_priority(otherOperator.m_priority)
{}

char dmitriev::Operator::getCondition() const
{
  return 2;
}
char dmitriev::Operator::getPriority() const
{
  return m_priority;
}
long long dmitriev::Operator::operator()(long long p1, long long p2)
{
  return m_mathOperator(p1, p2);
}
