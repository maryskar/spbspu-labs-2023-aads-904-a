#ifndef TRANSFORMINFIXQUEUETOPOSTFIX_H
#define TRANSFORMINFIXQUEUETOPOSTFIX_H
#include <stdexcept>
#include "queue.h"
#include "elem.h"
#include "stack.h"
#include "getpriority.h"
namespace tarasenko
{
  template< typename T >
  Queue< T > transformInfixQueueToPostfix(Queue< T >& q_infix)
  {
    Stack< Elem > s;
    Queue< Elem > q_postfix;
    bool was_open_bracket = false;
    while (!q_infix.isEmpty())
    {
      Elem elem = q_infix.drop();
      if (elem.isDigit())
      {
        q_postfix.push(elem);
      }
      else
      {
        if (s.isEmpty())
        {
          s.push(elem);
        }
        else if (elem.getValueOfOperation() == '(')
        {
          s.push(elem);
        }
        else if (elem.getValueOfOperation() == ')')
        {
          while (!s.isEmpty())
          {
            if (s.getTopElem().getValueOfOperation() == '(')
            {
              was_open_bracket = true;
              s.pop();
              break;
            }
            q_postfix.push(s.drop());
          }
          if (!was_open_bracket)
          {
            throw std::logic_error("Incorrect input");
          }
          was_open_bracket = false;
        }
        else
        {
          while (!s.isEmpty() && (getPriority(elem.getValueOfOperation()) <= getPriority(s.getTopElem().getValueOfOperation())))
          {
            q_postfix.push(s.drop());
          }
          s.push(elem);
        }
      }
    }
    while (!s.isEmpty())
    {
      q_postfix.push(s.drop());
    }
    return q_postfix;
  }
}
#endif
