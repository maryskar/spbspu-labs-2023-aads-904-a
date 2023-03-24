#include "convertToPostfixNotation.h"
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  Queue< std::string > convertToPostfixNotation(std::istream& inp, Stack< std::string >& stc,
                                                Queue< std::string >& que)
  {
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
        stc.push(var);
      }
      else if (var == ")")
      {
        std::string symb = stc.drop();
        while (symb != "(")
        {
          que.enqueue(symb);
          symb = stc.drop();
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
    }
    return que;
  }
}
