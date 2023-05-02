#include "notations.h"
#include <limits>
#include "priority.h"
#include "expressionpart.h"
constexpr long long maxLongLong = std::numeric_limits< long long >::max();
constexpr long long minLongLong = std::numeric_limits< long long >::min();
namespace romanovich
{
  using exp_q = Queue< ExpPart >;
  using exp_s = Stack< ExpPart >;
  bool doStackPopCondition(const ExpPart &q, const ExpPart &s)
  {
    try
    {
      if (q.isOperation() && s.isOperation())
      {
        Priority priorQ(q.getOperation());
        Priority priorS(s.getOperation());
        return (!(priorQ < priorS));
      }
      return false;
    }
    catch (...)
    {
      return false;
    }
  }
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
  ExpPart createFromString(const std::string &string)
  {
    const char sym = string[0];
    if (sym == as_char(parenthesis_t::right))
    {
      return ExpPart(parenthesis_t::right);
    }
    if (sym == as_char(parenthesis_t::left))
    {
      return ExpPart(parenthesis_t::left);
    }
    if (sym == as_char(operations_t::division))
    {
      return ExpPart(operations_t::division);
    }
    if (sym == as_char(operations_t::multiplication))
    {
      return ExpPart(operations_t::multiplication);
    }
    if (sym == as_char(operations_t::minus))
    {
      return ExpPart(operations_t::minus);
    }
    if (sym == as_char(operations_t::plus))
    {
      return ExpPart(operations_t::plus);
    }
    if (sym == as_char(operations_t::division_remainder))
    {
      return ExpPart(operations_t::division_remainder);
    }
    try
    {
      long long operand = std::stoll(string, nullptr, 10);
      return ExpPart(operand);
    }
    catch (...)
    {
      throw;
    }
  }
  long long doOperation(long long b, long long a, const operations_t &oper)
  {
    if (oper == operations_t::plus)
    {
      if (!overflowAdd(a, b))
      {
        return a + b;
      }
      else
      {
        throw std::overflow_error("");
      }
    }
    if (oper == operations_t::minus)
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
    if (oper == operations_t::multiplication)
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
    if (oper == operations_t::division)
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
  void getPostfixFromInfix(exp_q &queue, exp_s &stack, exp_q &postfixQueue)
  {
    while (!queue.isEmpty() or !stack.isEmpty())
    {
      if (!queue.isEmpty())
      {
        ExpPart qEl = queue.get();
        queue.pop();
        if (qEl.isParenthesis())
        {
          if (qEl.getParenthesis() == parenthesis_t::left)
          {
            stack.push(qEl);
          }
          if (qEl.getParenthesis() == parenthesis_t::right)
          {
            while (!stack.get().isParenthesis())
            {
              if (stack.get().isParenthesis())
              {
                if (stack.get().getParenthesis() == parenthesis_t::left)
                {
                  break;
                }
              }
              postfixQueue.push(stack.get());
              stack.pop();
              if (stack.isEmpty())
              {
                break;
              }
            }
            stack.pop();
          }
        }
        if (qEl.isOperand())
        {
          postfixQueue.push(qEl);
        }
        if (qEl.isOperation())
        {
          if (!stack.isEmpty())
          {
            if (doStackPopCondition(qEl, stack.get()))
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
  Queue< ExpPart > splitLine(const std::string &string)
  {
    Queue< ExpPart > queue;
    int intBegin = 0;
    int intEnd = string.find(' ');
    while (intEnd != -1)
    {
      queue.push(createFromString(string.substr(intBegin, intEnd - intBegin)));
      intBegin = intEnd + 1;
      intEnd = string.find(' ', intBegin);
    }
    queue.push(createFromString(string.substr(intBegin, intEnd - intBegin)));
    return queue;
  }
  void calcPostfixExpression(exp_q &postfixQueue, exp_s &answer, exp_s &stack)
  {
    stack.push(postfixQueue.get());
    postfixQueue.pop();
    while (!stack.isEmpty())
    {
      if (postfixQueue.isEmpty())
      {
        break;
      }
      ExpPart expPart(postfixQueue.get());
      postfixQueue.pop();
      if (expPart.isOperand())
      {
        stack.push(expPart);
      }
      else
      {
        try
        {
          long long x = std::stoll(std::to_string(stack.get().getOperand()), nullptr, 10);
          stack.pop();
          long long y = std::stoll(std::to_string(stack.get().getOperand()), nullptr, 10);
          stack.pop();
          stack.push(ExpPart(doOperation(x, y, expPart.getOperation())));
        }
        catch (...)
        {
          throw std::range_error("Error calculating postfix.");
        }
      }
    }
    answer.push(stack.get());
  }
}
