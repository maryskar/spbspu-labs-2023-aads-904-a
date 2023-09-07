#include "getPostfixForm.h"
#include <string>
#include <stdexcept>
#include "stack.h"
#include "queue.h"
#include "Splitter.h"
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
  Queue< std::string > getPostfixForm(std::string infix)
  {
    Queue< std::string > postfix;
    Stack< char > opStack;
    timofeev::Splitter split(infix);
    while (!split.empty())
    {
      const std::string &c = split.getSplit();
      try
      {
        std::stoll(c);
        postfix.push(c);
      }
      catch (const std::invalid_argument &)
      {
        if (c == "(")
        {
          opStack.push(c[0]);
        }
        else if (c == ")")
        {

          while (!opStack.isEmpty() && opStack.drop() != '(')
          {
            postfix.push(std::string(1, opStack.drop()));
            opStack.pop();
          }
          opStack.pop();
        }
        else
        {
          if (!opStack.isEmpty())
          {
            char p = opStack.drop();
            while (p != '(' && getPriority(p) >= getPriority(c[0]))
            {
              postfix.push(std::string(1, p));
              opStack.pop();
              if (opStack.isEmpty())
              {
                break;
              }
              p = opStack.drop();
            }
          }
          opStack.push(c[0]);
        }
      }
    }
    while (!opStack.isEmpty())
    {
      postfix.push(std::string(1, opStack.drop()));
      opStack.pop();
    }
    return postfix;
  }
}
