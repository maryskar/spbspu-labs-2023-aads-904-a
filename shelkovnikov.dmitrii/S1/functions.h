#ifndef SPBSPU_LABS_2023_AADS_904_A_FUNCTIONS_H
#define SPBSPU_LABS_2023_AADS_904_A_FUNCTIONS_H
#include <string>
#include "queue.h"
#include "parser.h"
#include "part.h"
#include "stack.h"
namespace dimkashelk
{
  bool isPriorityOperation(char first, char second);
  int getResult(int first, int second, char oper);
  template< typename T >
  Queue< T > getQueueOfArithmeticExpression(std::string element)
  {
    Parser parser(element);
    Queue< part > data;
    while (parser.hasNext())
    {
      data.push(makePart(parser()));
    }
    return data;
  }
  template< typename T >
  Queue< T > getPolandArithmeticExpression(Queue< T > data)
  {
    Queue< part > queue;
    Stack< part > stack;
    while (!data.empty())
    {
      part p = data.drop();
      if (!p.isDigit_)
      {
        if (p.operator_ == ')')
        {
          if (stack.empty())
          {
            throw std::logic_error("Check expression");
          }
          part p1 = stack.drop();
          while (p1.operator_ != '(')
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
          part p1 = stack.drop();
          stack.push(p1);
          if (isPriorityOperation(p1.operator_, p.operator_) || p1.operator_ == '(')
          {
            stack.push(p);
          }
          else
          {
            p1 = stack.drop();
            while (!isPriorityOperation(p1.operator_, p.operator_))
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
