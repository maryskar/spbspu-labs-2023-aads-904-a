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
          Elem res(0ll);
          long long b = s.drop().getValueOfOperand();
          long long a = s.drop().getValueOfOperand();
          res = calculate(a, b, elem.getValueOfOperation());
          s.push(res);
        }
      }
    }
    return s.drop().getValueOfOperand();
  };
}
#endif
