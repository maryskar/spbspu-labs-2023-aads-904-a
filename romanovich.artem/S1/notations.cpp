#include "notations.h"
#include "priority.h"
#include <limits>
#include <algorithm>
namespace romanovich
{
  int signum(long long n)
  {
    return (n > 0) - (n < 0);
  }
  bool overflowAdd(long long a, long long b, long long maxLongLong, long long minLongLong)
  {
    if (signum(a) == signum(b))
    {
      return ((b > 0 && a > maxLongLong - b) || (b < 0 && a < minLongLong - b));
    }
    return false;
  }
  bool overflowMult(long long a, long long b, long long maxLongLong, long long minLongLong)
  {
    return ((a != 0 && b != 0) && ((a > maxLongLong / b) || (a < minLongLong / b)));
  }
  bool overflowSubt(long long a, long long b, long long maxLongLong, long long minLongLong)
  {
    return ((b < 0 && a > maxLongLong + b) || (b > 0 && a < minLongLong + b));
  }
}
bool romanovich::isOperator(const std::string &c)
{
  return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
}
bool romanovich::isDigit(const std::string &str)
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
bool romanovich::stackPopCondition(const std::string &q, const std::string &s)
{
  try
  {
    romanovich::Priority priorQ(q);
    romanovich::Priority priorS(s);
    return (priorQ >= priorS);
  }
  catch (...)
  {
    return false;
  }
}
romanovich::Queue< std::string > romanovich::getPostfixFromInfix(romanovich::Queue< std::string > queue)
{
  romanovich::Queue< std::string > postfixQueue;
  romanovich::Stack< std::string > *stack = new Stack< std::string >;
  while (!queue.isEmpty() or !stack->isEmpty())
  {
    if (!queue.isEmpty())
    {
      std::string qEl = queue.pop();
      if (qEl == "(")
      {
        stack->push(qEl);
      }
      if (qEl == ")")
      {
        while (stack->get() != "(")
        {
          postfixQueue.push(stack->get());
          stack->pop();
          if (stack->isEmpty())
          {
            break;
          }
        }
        stack->pop();
      }
      try
      {
        std::stoll(qEl, nullptr, 10);
      }
      catch (...)
      {
        if (!stack->isEmpty())
        {
          if (stackPopCondition(qEl, stack->get()))
          {
            postfixQueue.push(stack->get());
            stack->pop();
          }
        }
        stack->push(qEl);
      }
      postfixQueue.push(qEl);
    }
    else
    {
      while (!stack->isEmpty())
      {
        postfixQueue.push(stack->get());
        stack->pop();
      }
    }
  }
  delete stack;
  return postfixQueue;
}
romanovich::Queue< std::string > romanovich::splitLine(const std::string &string)
{
  romanovich::Queue< std::string > queue;
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
std::string romanovich::doOperation(long long b, long long a, const std::string &oper)
{
  long long maxLongLong = std::numeric_limits< long long >::max();
  long long minLongLong = std::numeric_limits< long long >::min();
  if (oper == "+")
  {
    if (!romanovich::overflowAdd(a, b, maxLongLong, minLongLong))
    {
      return std::to_string(a + b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "-")
  {
    if (!romanovich::overflowSubt(a, b, maxLongLong, minLongLong))
    {
      return std::to_string(a - b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (oper == "*")
  {
    if (!romanovich::overflowMult(a, b, maxLongLong, minLongLong))
    {
      return std::to_string(a * b);
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
      return std::to_string(a / b);
    }
    else
    {
      throw std::overflow_error("");
    }
  }
  if (a < 0)
  {
    return std::to_string((a % b) + b);
  }
  return std::to_string(a % b);
}
void romanovich::calcPostfixExpression(Queue< std::string > postfixQueue, Stack< std::string > *answer, Stack< std::string > *calcStack)
{
  calcStack->push(postfixQueue.pop());
  while (!calcStack->isEmpty())
  {
    std::string el;
    if (!postfixQueue.isEmpty())
    {
      el = postfixQueue.pop();
    }
    else
    {
      break;
    }
    if (romanovich::isDigit(el))
    {
      calcStack->push(el);
    }
    else
    {
      try
      {
        long long x = std::stoll(calcStack->get(), nullptr, 10);
        long long y = std::stoll(calcStack->get(), nullptr, 10);
        calcStack->pop();
        calcStack->pop();
        calcStack->push(romanovich::doOperation(x, y, el));
      }
      catch (...)
      {
        delete calcStack;
        throw;
      }
    }
  }
  answer->push(calcStack->get());
  delete calcStack;
}
