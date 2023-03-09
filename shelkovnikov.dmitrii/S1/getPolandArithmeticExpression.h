#ifndef SPBSPU_LABS_2023_AADS_904_A_GETPOLANDARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETPOLANDARITHMETICEXPRESSION_H
#include <string>
#include "queue.h"
#include "partOfArithmeticExpression.h"
#include "stack.h"
#include "getResultOfArithmeticExpression.h"
namespace dimkashelk
{
  Queue< PartOfArithmeticExpression > getPolandArithmeticExpression(Queue< PartOfArithmeticExpression > &data)
  {
    Queue< PartOfArithmeticExpression > queue;
    Stack< PartOfArithmeticExpression > stack;
    while (!data.empty())
    {
      PartOfArithmeticExpression p = data.front();
      if (!p.isDigit)
      {
        if (p.element.operator_ == ')')
        {
          if (stack.empty())
          {
            throw std::logic_error("Check expression");
          }
          PartOfArithmeticExpression p1 = stack.last();
          stack.pop_back();
          while (p1.element.operator_ != '(')
          {
            queue.push(p1);
            if (stack.empty())
            {
              throw std::logic_error("Check expression");
            }
            p1 = stack.last();
            stack.pop_back();
          }
        }
        else if (stack.empty())
        {
          stack.push(p);
        }
        else
        {
          PartOfArithmeticExpression p1 = stack.last();
          stack.pop_back();
          stack.push(p1);
          if (isGreaterPriority(p1, p) || p1.element.operator_ == '(')
          {
            stack.push(p);
          }
          else
          {
            p1 = stack.last();
            stack.pop_back();
            while (!isGreaterPriority(p1, p))
            {
              queue.push(p1);
              if (stack.empty())
              {
                break;
              }
              p1 = stack.last();
              stack.pop_back();
            }
            stack.push(p);
          }
        }
      }
      else
      {
        queue.push(p);
      }
    }
    while (!stack.empty())
    {
      queue.push(stack.last());
      stack.pop_back();
    }
    return queue;
  }
}
#endif
