#ifndef TRANSFORMINFIXQUEUETOPOSTFIX_H
#define TRANSFORMINFIXQUEUETOPOSTFIX_H
#include <stdexcept>
#include "queue.h"
#include "elem.h"
#include "stack.h"
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
        else if (elem.getOperation().getValue() == '(')
        {
          s.push(elem);
        }
        else if (elem.getOperation().getValue() == ')')
        {
          while (!s.isEmpty())
          {
            if (s.getTopElem().getOperation().getValue() == '(')
            {
              was_open_bracket = true;
              s.pop();
              break;
            }
            Elem s_elem = s.drop();
            q_postfix.push(s_elem);
          }
          if (!was_open_bracket)
          {
            throw std::logic_error("Incorrect input");
          }
          was_open_bracket = false;
        }
        else
        {
          while (!s.isEmpty() && (elem.getOperation() <= s.getTopElem().getOperation()))
          {
            Elem s_elem = s.drop();
            q_postfix.push(s_elem);
          }
          s.push(elem);
        }
      }
    }
    while (!s.isEmpty())
    {
      Elem s_elem = s.drop();
      q_postfix.push(s_elem);
    }
    return q_postfix;
  }
}
#endif
