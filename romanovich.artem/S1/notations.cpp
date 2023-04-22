#include "notations.h"
#include "priority.h"
#include "expressionpart.h"
#include <limits>
#include <algorithm>
constexpr long long maxLongLong = std::numeric_limits< long long >::max();
constexpr long long minLongLong = std::numeric_limits< long long >::min();
using exp_q = romanovich::Queue< ExpPart >;
using exp_s = romanovich::Stack< ExpPart >;
namespace romanovich
{
  int signum(long long n)
  {
    return (n > 0) - (n < 0);
  }
  bool overflowAdd(long long a, long long b)
  {
    if (signum(a) == signum(b))
    {
      return ((b > 0 && a > maxLongLong - b) || (b < 0 && a < minLongLong - b));
    }
    return false;
  }
  bool overflowMult(long long a, long long b)
  {
    return ((a != 0 && b != 0) && ((a > maxLongLong / b) || (a < minLongLong / b)));
  }
  bool overflowSubt(long long a, long long b)
  {
    return ((b < 0 && a > maxLongLong + b) || (b > 0 && a < minLongLong + b));
  }
}
bool romanovich::isOperator(const ExpPart &c)
{
  return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
}
bool romanovich::isDigit(const ExpPart &str)
{
  try
  {
    std::stoll(str, nullptr, 10);
  }
  catch (...)
  {
    return false;
  }
  return true;
}
bool romanovich::stackPopCondition(const ExpPart &q, const ExpPart &s)
{
  try
  {
    romanovich::Priority priorQ(q);
    romanovich::Priority priorS(s);
    return (!(priorQ < priorS));
  }
  catch (...)
  {
    return false;
  }
}
void romanovich::getPostfixFromInfix(exp_q &queue, exp_s &stack, exp_q &postfixQueue)
{
  while (!queue.isEmpty() or !stack.isEmpty())
  {
    if (!queue.isEmpty())
    {
      ExpPart qEl = queue.get();
      queue.pop();
      if (qEl == "(")
      {
        stack.push(qEl);
      }
      if (qEl == ")")
      {
        while (stack.get() != "(")
        {
          postfixQueue.push(stack.get());
          stack.pop();
          if (stack.isEmpty())
          {
            break;
          }
        }
        stack.pop();
      }
      if (isDigit(qEl))
      {
        postfixQueue.push(qEl);
      }
      if (isOperator(qEl))
      {
        if (!stack.isEmpty())
        {
          if (stackPopCondition(qEl, stack.get()))
          {
            postfixQueue.push(stack.get());
            stack.pop();
          }
        }
        stack.push(qEl);
      }
    }
    else
    {
      while (!stack.isEmpty())
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
    }
  }
}
romanovich::Queue< ExpPart > romanovich::splitLine(const std::string &string)
{
  romanovich::Queue< ExpPart > queue;
  int intBegin = 0;
  int intEnd = string.find(' ');
  while (intEnd != -1)
  {
    queue.push(string.substr(intBegin, intEnd - intBegin));
    intBegin = intEnd + 1;
    intEnd = string.find(' ', intBegin);
  }
  queue.push(string.substr(intBegin, intEnd - intBegin));
  return queue;
}
ExpPart romanovich::doOperation(long long b, long long a, const ExpPart &oper)
{
  if (oper == "+")
  {
    if (!romanovich::overflowAdd(a, b))
    {
      return a + b;
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "-")
  {
    if (!romanovich::overflowSubt(a, b))
    {
      return a - b;
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "*")
  {
    if (!romanovich::overflowMult(a, b))
    {
      return a * b;
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "/")
  {
    if (b != 0)
    {
      return a / b;
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (a < 0)
  {
    return ((a % b) + b);
  }
  return a % b;
}
void romanovich::calcPostfixExpression(exp_q &postfixQueue, exp_s &answer, exp_s &stack)
{
  stack.push(postfixQueue.get());
  postfixQueue.pop();
  while (!stack.isEmpty())
  {
    ExpPart expPart;
    if (!postfixQueue.isEmpty())
    {
      expPart = postfixQueue.get();
      postfixQueue.pop();
    }
    else
    {
      break;
    }
    if (romanovich::isDigit(expPart))
    {
      stack.push(expPart);
    }
    else
    {
      try
      {
        long long x = std::stoll(stack.get(), nullptr, 10);
        stack.pop();
        long long y = std::stoll(stack.get(), nullptr, 10);
        stack.pop();
        stack.push(romanovich::doOperation(x, y, expPart));
      }
      catch (...)
      {
        throw std::range_error("Error calculating postfix.");
      }
    }
  }
  answer.push(stack.get());
}
