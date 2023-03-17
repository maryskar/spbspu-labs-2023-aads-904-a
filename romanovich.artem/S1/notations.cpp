#include "notations.h"
#include "priority.h"
#include <limits>
#include <algorithm>
long long maxLongLong = std::numeric_limits< long long >::max();
long long minLongLong = std::numeric_limits< long long >::min();
int sgn(long long n)
{
  return (n > 0) - (n < 0);// (n > 0) ? 1 : ((n < 0) ? -1 : 0);
}
bool overflowAdd(long long a, long long b)
{
  if (sgn(a) == sgn(b))
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
bool isOperator(const std::string &c)
{
  return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
}
bool isDigit(const std::string &str)
{
  return std::all_of(str.begin(), str.end(), ::isdigit);
}
bool stackPopCondition(const std::string &q, const std::string &s)
{
  //if (isOperator(s) && !isDigit(s))
  //{
  try
  {
    Priority priorQ(q);
    Priority priorS(s);
    return (priorQ >= priorS);
  } catch (...)
  {
    return false;
  }
}
Queue< std::string > getPostfixFromInfix(Queue< std::string > queue)
{
  Queue< std::string > postfixQueue;
  Stack< std::string > *stack = new Stack< std::string >;
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
        while (stack->getTop() != "(")
        {
          postfixQueue.push(stack->pop());
          if (stack->isEmpty())
          {
            break;
          }
        }
        stack->pop();
      }
      if (std::all_of(qEl.begin(), qEl.end(), ::isdigit))// && !isDigit(q)
      {
        postfixQueue.push(qEl);
      }
      if (isOperator(qEl))
      {
        if (!stack->isEmpty())
        {
          if (stackPopCondition(qEl, stack->getTop()))
          {
            postfixQueue.push(stack->pop());
          }
        }
        stack->push(qEl);
      }
    }
    else
    {
      while (!stack->isEmpty())
      {
        postfixQueue.push(stack->pop());
      }
    }
  }
  delete stack;
  return postfixQueue;
}
Queue< std::string > splitLine(const std::string &string)
{
  Queue< std::string > queue;
  int begin = 0;
  int end = string.find(' ');
  while (end != -1)
  {
    queue.push(string.substr(begin, end - begin));
    begin = end + 1;
    end = string.find(' ', begin);
  }
  queue.push(string.substr(begin, end - begin));
  return queue;
}
std::string doOperation(long long b, long long a, const std::string &oper)
{
  if (oper == "+")
  {
    if (!overflowAdd(a, b))
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
    if (!overflowSubt(a, b))
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
    if (!overflowMult(a, b))
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
void calcPostfixExpression(Queue< std::string > postfixQueue, Stack< std::string > *answer)
{
  Stack< std::string > *calcStack = new Stack< std::string >;
  calcStack->push(postfixQueue.pop());
  while (calcStack->getSize() >= 1)
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
    //if (isDigit(el))
    if (std::isdigit(static_cast<int> (std::stoll(el, nullptr, 10))))
    {
      calcStack->push(el);
    }
    else
    {
      try
      {
        long long x = std::stoll(calcStack->pop(), nullptr, 10);
        long long y = std::stoll(calcStack->pop(), nullptr, 10);
        calcStack->push(doOperation(x, y, el));
      }
      catch (...)
      {
        delete calcStack;
        throw;
      }
    }
  }
  answer->push(calcStack->getTop());
  delete calcStack;
}
