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
  else if (var == "*" || var == "/")
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
  Queue< std::string > convertToPostfixNotation(std::istream& inp, Stack< std::string >& stc, Queue< std::string >& que)
  {
    size_t countOfBrackets = 0;
    std::string var;
    while (inp)
    {
      inp >> var;
      if (!inp)
      {
        break;
      }
      short int NumOfOp = returnNumbOfOper(var);
      if (NumOfOp == 0)
      {
        stc.push(var);
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
          stc.push(var);
        }
        else if (returnNumbOfOper(stc.drop()) >= NumOfOp)
        {
          que.enqueue(stc.drop());
          stc.pop();
          stc.push(var);
        }
        else
        {
          stc.push(var);
        }
      }
      else if (NumOfOp == 4)
      {
        que.enqueue(var);
      }
    }
    while (stc.isEmpty())
    {
      que.enqueue(stc.drop());
      stc.pop();
    }
    return que;
  }
}
