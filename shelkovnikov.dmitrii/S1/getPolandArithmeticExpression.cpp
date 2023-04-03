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
    data.pop_front();
    if (!p.isDigit)
    {
      if (p.isBracket && p.element.operator_ == ')')
      {
        if (stack.empty())
        {
          throw std::logic_error("Check expression");
        }
        dsk::PartOfArithExpr p1 = stack.last();
        stack.pop_back();
        while (!p1.isBracket && p1.element.bracket_ != '(')
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
        dsk::PartOfArithExpr p1 = stack.last();
        if (p1.isBracket || p.isBracket || isGreaterPriority(p1, p))
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
