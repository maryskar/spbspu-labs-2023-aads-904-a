#ifndef SPBSPU_LABS_2023_AADS_904_A_GETPOLANDARITHMETICEXPRESSION_H
#define SPBSPU_LABS_2023_AADS_904_A_GETPOLANDARITHMETICEXPRESSION_H
#include <string>
#include "queue.h"
#include "partOfArithmeticExpression.h"
#include "stack.h"
#include "functions.h"
namespace dimkashelk
{
  Queue< PartOfArithmeticExpression > getPolandArithmeticExpression(Queue< PartOfArithmeticExpression > data)
  {
    Queue< PartOfArithmeticExpression > queue;
    Stack< PartOfArithmeticExpression > stack;
    while (!data.empty())
    {
      PartOfArithmeticExpression p = data.drop();
      if (!p.isDigit)
      {
        if (p.element.operator_ == ')')
        {
          if (stack.empty())
          {
            throw std::logic_error("Check expression");
          }
          PartOfArithmeticExpression p1 = stack.drop();
          while (p1.element.operator_ != '(')
          {
            queue.push(p1);
            if (stack.empty())
            {
              throw std::logic_error("Check expression");
            }
            p1 = stack.drop();
          }
        }
        else if (stack.empty())
        {
          stack.push(p);
        }
        else
        {
          PartOfArithmeticExpression p1 = stack.drop();
          stack.push(p1);
          if (isPriorityOperation(p1.element.operator_, p.element.operator_) || p1.element.operator_ == '(')
          {
            stack.push(p);
          }
          else
          {
            p1 = stack.drop();
            while (!isPriorityOperation(p1.element.operator_, p.element.operator_))
            {
              queue.push(p1);
              if (stack.empty())
              {
                break;
              }
              p1 = stack.drop();
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
      queue.push(stack.drop());
    }
    return queue;
  }
}
#endif
