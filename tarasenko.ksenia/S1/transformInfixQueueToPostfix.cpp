#include "transformInfixQueueToPostfix.h"
#include <stdexcept>
#include "stack.h"
#include "queue.h"
#include "elem.h"

tarasenko::Queue< tarasenko::Elem > tarasenko::transformInfixQueueToPostfix(Queue< Elem >& q_infix)
{
  Stack< Elem > s;
  Queue< Elem > q_postfix;
  bool was_open_bracket = false;
  while (!q_infix.isEmpty())
  {
    Elem elem = q_infix.getHeadElem();
    q_infix.popFront();
    if (elem.isNumber())
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
          Elem s_elem = s.getTopElem();
          s.pop();
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
        while (!s.isEmpty() && (s.getTopElem().getOperation() >= elem.getOperation()))
        {
          Elem s_elem = s.getTopElem();
          s.pop();
          q_postfix.push(s_elem);
        }
        s.push(elem);
      }
    }
  }
  while (!s.isEmpty())
  {
    Elem s_elem = s.getTopElem();
    s.pop();
    q_postfix.push(s_elem);
  }
  return q_postfix;
}
