#include "getPolandArithmeticExpression.h"
#include "stack.h"
dimkashelk::Queue< dimkashelk::PartOfArithExpr > dimkashelk::getPolandArithExpr(dimkashelk::Queue< dimkashelk::PartOfArithExpr > &data)
{
  namespace dsk = dimkashelk;
  dsk::Queue< dsk::PartOfArithExpr > queue;
  dsk::Stack< dsk::PartOfArithExpr > stack;
  while (!data.empty())
  {
    dsk::PartOfArithExpr p = data.front();
    data.popFront();
    if (!p.isDigit())
    {
      if (p.isBracket() && p.getParenthesis().isClose())
      {
        if (stack.empty())
        {
          throw std::logic_error("Check expression");
        }
        dsk::PartOfArithExpr p1 = stack.front();
        stack.popFront();
        while (!p1.isBracket())
        {
          queue.push(p1);
          if (stack.empty())
          {
            throw std::logic_error("Check expression");
          }
          p1 = stack.front();
          stack.popFront();
        }
      }
      else if (stack.empty())
      {
        stack.pushFront(p);
      }
      else
      {
        dsk::PartOfArithExpr p1 = stack.front();
        if (p1.isBracket() || p.isBracket() || isGreaterPriority(p1.getOperator(), p.getOperator()))
        {
          stack.pushFront(p);
        }
        else
        {
          p1 = stack.front();
          stack.popFront();
          while (!isGreaterPriority(p1.getOperator(), p.getOperator()))
          {
            queue.push(p1);
            if (stack.empty())
            {
              break;
            }
            p1 = stack.front();
            stack.popFront();
          }
          stack.pushFront(p);
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
    queue.push(stack.front());
    stack.popFront();
  }
  return queue;
}
