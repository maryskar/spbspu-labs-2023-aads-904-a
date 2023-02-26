#ifndef CALCULATEBYPOSTFIXQUEUE_H
#define CALCULATEBYPOSTFIXQUEUE_H
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "calculate.h"

template< typename T >
int calculateByPostfixQueue(Queue< T >& q_postfix)
{
  Elem elem;
  Stack< Elem > s;
  while (!q_postfix.isEmpty())
  {
    elem = q_postfix.drop();
    if (elem.is_int)
    {
      s.push(elem);
    }
    else
    {
      if (!s.isEmpty())
      {
        Elem res{true, 0};
        int b = s.drop().union_elem.operand;
        int a = s.drop().union_elem.operand;
        try
        {
          res.union_elem.operand = calculate< int >(a, b, elem.union_elem.operation);
          s.push(res);
        }
        catch (const std::exception& e)
        {
          throw;
        }
      }
    }
  }
  return s.drop().union_elem.operand;
};

#endif
