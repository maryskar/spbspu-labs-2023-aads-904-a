#include "convertToPostfixNotation.h"
#include <string>
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
  else
  {
    return 4;
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
        short int NumOfOp = returnNumbOfOper(op);
        if (NumOfOp == 0)
        {
          stc.push(op);
        }
        else if (NumOfOp == 1)
        {
          while (stc.drop() != "(")
          {
            que.enqueue(stc.drop());
            stc.pop();
          }
          stc.pop();
        }
        else if (NumOfOp == 2 || NumOfOp == 3)
        {
          if (!stc.isEmpty())
          {
            stc.push(op);
          }
          else if (returnNumbOfOper(stc.drop()) >= NumOfOp)
          {
            que.enqueue(stc.drop());
            stc.pop();
            stc.push(op);
          }
          else
          {
            stc.push(op);
          }
        }
        else if (NumOfOp == 4)
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
      que.enqueue(stc.drop());
      stc.pop();
    }
  }
}
