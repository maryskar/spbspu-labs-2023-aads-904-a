#include "convertToPostfixNotation.h"
#include <string>
#include "isLessPriority.h"
#include "queue.h"
#include "stack.h"

short int returnNumbOfOper(std::string var)
{
  if (var == "(")
  {
    return 0;
  }
  else if (var == ")")
  {
    return 1;
  }
  else if (var == "+" || var == "-")
  {
    return 2;
  }
  else if (var == "*" || var == "/" || var == "%")
  {
    return 3;
  }
}

namespace mashkin
{
  void convertToPostNot(const std::string& line, Stack< std::string >& stc, Queue< std::string >& que)
  {
    std::string op;
    for (auto symb : line)
    {
      if (symb == ' ')
      {
        if (!op.find_first_of("()-+*/%"))
        {
          short int NumOfOp = returnNumbOfOper(op);
          if (NumOfOp == 0)
          {
            stc.push(op);
          }
          else if (NumOfOp == 1)
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
            if (isLessPriority(returnNumbOfOper(stc.getTop()), NumOfOp))
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
      que.enqueue(stc.getTop());
      stc.pop();
    }
  }
}
