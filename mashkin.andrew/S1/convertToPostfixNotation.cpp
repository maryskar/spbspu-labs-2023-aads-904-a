#include "convertToPostfixNotation.h"
#include "stack.h"
#include "queue.h"

void convertToPostfixNotation(std::ifstream& inpFile, Stack< char > stc, Queue< char > que)
{
  char var;
  while (!inpFile)
  {
    inpFile >> var;
    if (var == '(' || var == '+' || var == '-' || var == '*' || var == '/' || var == '%')
    {
      stc.push(var);
    }
    else if (var == ')')
    {
      char symb = stc.drop();
      while (symb != '(')
      {}
    }
  }
}
