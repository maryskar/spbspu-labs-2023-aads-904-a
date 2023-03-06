#ifndef CALCULATEBYPOSTFIXQUEUE_H
#define CALCULATEBYPOSTFIXQUEUE_H
#include "queue.h"
#include "stack.h"
#include "elem.h"
#include "calculate.h"
namespace tarasenko
{
  long long calculateByPostfixQueue(Queue< Elem >& q_postfix)
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
          long long b = s.drop().union_elem.operand;
          long long a = s.drop().union_elem.operand;
          res.union_elem.operand = calculate(a, b, elem.union_elem.operation);
          s.push(res);
        }
      }
    }
    return s.drop().union_elem.operand;
  };
}
#endif
