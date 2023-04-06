#include "convertToPostfixNotation.h"
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  Queue< std::string > convertToPostfixNotation(std::istream& inp, Stack< std::string >& stc,
                                                Queue< std::string >& que)
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
      if (var == "(" || var == "+" || var == "-" || var == "*" || var == "/" || var == "%")
      {
        if (var == "(")
        {
          countOfBrackets++;
        }
        if (countOfBrackets == 0 && stc.isEmpty())
        {
          que.enqueue(stc.drop());
          stc.pop();
        }
        stc.push(var);
      }
      else if (var == ")")
      {
        std::string symb = stc.drop();
        stc.pop();
        while (symb != "(")
        {
          que.enqueue(symb);
          symb = stc.drop();
          stc.pop();
          if (var == "(")
          {
            countOfBrackets--;
          }
        }
      }
      else
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
