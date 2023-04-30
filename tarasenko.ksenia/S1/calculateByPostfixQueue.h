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
      Elem elem = q_postfix.getHeadElem();
      q_postfix.popFront();
      if (elem.isNumber())
      {
        s.push(elem);
      }
      else
      {
        if (!s.isEmpty())
        {
          long long b = s.getTopElem().getOperand();
          s.pop();
          long long a = s.getTopElem().getOperand();
          s.pop();
          Elem res(calculate(a, b, elem.getOperation().getValue()));
          s.push(res);
        }
      }
    }
    Elem res = s.getTopElem();
    s.pop();
    return res.getOperand();
  }
}
#endif
