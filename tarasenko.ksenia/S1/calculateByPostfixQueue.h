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
    Stack< Elem > s;
    while (!q_postfix.isEmpty())
    {
      Elem elem = q_postfix.drop();
      if (elem.isDigit())
      {
        s.push(elem);
      }
      else
      {
        if (!s.isEmpty())
        {
          long long b = s.drop().getOperand();
          long long a = s.drop().getOperand();
          Elem res = calculate(a, b, elem.getOperation().getValue());
          s.push(res);
        }
      }
    }
    return s.drop().getOperand();
  };
}
#endif
