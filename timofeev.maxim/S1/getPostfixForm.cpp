#include "getPostfixForm.h"
#include <stdexcept>
int getPriority(char op)
{
  if (op == '+' || op == '-')
  {
    return 1;
  }
  else if (op == '*' || op == '/' || op == '%')
  {
    return 2;
  }
  else
  {
    throw std::logic_error("No opperand in string");
  }
}
namespace timofeev
{
  Queue<std::string> getPostfixForm(std::string infix)
  {
    Queue<std::string> postfix;
    Stack<char> opStack;
    while ()
    {
      try
      {
        std::stoll(c);
      }
    }
  }
}