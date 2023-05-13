#include "notations.h"
#include "priority.h"
#include "expressionpart.h"
using exp_q = romanovich::Queue< romanovich::ExpPart >;
using exp_s = romanovich::Stack< romanovich::ExpPart >;
void romanovich::getPostfixFromInfix(exp_q &queue, exp_s &stack, exp_q &postfixQueue)
{
  while (!queue.isEmpty() or !stack.isEmpty())
  {
    if (!queue.isEmpty())
    {
      romanovich::ExpPart qEl = queue.get();
      queue.pop();
      if (qEl.isParenthesis())
      {
        if (qEl.getParenthesis() == romanovich::parenthesis_t::left)
        {
          stack.push(qEl);
        }
        if (qEl.getParenthesis() == romanovich::parenthesis_t::right)
        {
          while (!stack.get().isParenthesis())
          {
            if (stack.get().isParenthesis())
            {
              if (stack.get().getParenthesis() == romanovich::parenthesis_t::left)
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
          bool canPop = false;
          const romanovich::ExpPart q = qEl;
          const romanovich::ExpPart s = stack.get();
          try
          {
            if (q.isOperation() && s.isOperation())
            {
              romanovich::Priority priorQ(q.getOperation());
              romanovich::Priority priorS(s.getOperation());
              canPop = (!(priorQ < priorS));
            }
          }
          catch (...)
          {
            canPop = false;
          }
          if (canPop)
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
romanovich::Queue< romanovich::ExpPart > romanovich::splitLine(const std::string &string)
{
  romanovich::Queue< romanovich::ExpPart > queue;
  size_t intBegin = 0;
  size_t intEnd = string.find(' ');
  while (intEnd != std::string::npos)
  {
    queue.push(createFromString(string.substr(intBegin, intEnd - intBegin)));
    intBegin = intEnd + 1;
    intEnd = string.find(' ', intBegin);
  }
  queue.push(createFromString(string.substr(intBegin, intEnd - intBegin)));
  return queue;
}
void romanovich::calcPostfixExpression(exp_q &postfixQueue, exp_s &answer, exp_s &stack)
{
  stack.push(postfixQueue.get());
  postfixQueue.pop();
  while (!stack.isEmpty())
  {
    if (postfixQueue.isEmpty())
    {
      break;
    }
    romanovich::ExpPart expPart(postfixQueue.get());
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
        stack.push(romanovich::ExpPart(doOperation(x, y, expPart.getOperation())));
      }
      catch (...)
      {
        throw std::range_error("Error calculating postfix.");
      }
    }
  }
  answer.push(stack.get());
}
