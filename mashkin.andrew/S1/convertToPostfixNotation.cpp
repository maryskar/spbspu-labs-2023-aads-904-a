#include "convertToPostfixNotation.h"
#include <string>
#include "queue.h"
#include "stack.h"

namespace mashkin
{
  void convertToPostfixNotation(std::ifstream& inpFile, Stack< std::string >& stc, Queue< std::string >& que)
  {
    std::string var;
    while (inpFile)
    {
      inpFile >> var;
      if (!inpFile)
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
  }
}
