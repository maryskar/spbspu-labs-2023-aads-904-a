#include "convertToPostfixNotation.h"
#include <string>
#include "isLessPriority.h"
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostNot(const std::string& line, Queue< std::string >& que)
  {
    mashkin::Stack< std::string > stc;
    std::string op;
    for (auto symb: line)
    {
      if (symb == ' ')
      {
        if (!op.find_first_of("()-+*/%"))
        {
          if (op == "(")
          {
            stc.push(op);
          }
          else if (op == ")")
          {
            while (stc.getTop() != "(")
            {
              que.enqueue(stc.getTop());
              stc.pop();
            }
            stc.pop();
          }
          else if (!stc.isEmpty())
          {
            stc.push(op);
          }
          else
          {
            if (isLessPriority(stc.getTop(), op))
            {
              while (stc.isEmpty())
              {
                que.enqueue(stc.getTop());
                stc.pop();
              }
              stc.push(op);
            }
            else
            {
              stc.push(op);
            }
          }
        }
        else
        {
          que.enqueue(op);
        }
        op = "";
      }
      else
      {
        op += symb;
      }
    }
    while (stc.isEmpty())
    {
      if (stc.getTop() == "(")
      {
        throw std::logic_error("There are parentheses");
      }
      que.enqueue(stc.getTop());
      stc.pop();
    }
  }
}
