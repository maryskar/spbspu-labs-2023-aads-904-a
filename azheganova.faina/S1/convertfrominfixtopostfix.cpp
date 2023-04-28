#include "convertfrominfixtopostfix.h"
#include <cctype>

bool isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
}

void convertFromInfixToPostfix(q_n & queue, s_n & stack, q_n & postfix)
{
  while (!queue.isEmpty())
  {
    std::string element = queue.drop();
    queue.pop();
    if (isdigit(element[0]))
    {
      postfix.push(element);
    }
    else if (element == "(")
    {
      stack.push(element);
    }
    else if (element == ")")
    {
      while (stack.drop() != "(")
      {
        postfix.push(stack.drop());
        stack.pop();
        if (stack.isEmpty())
        {
          break;
        }
      }
      stack.pop();
    }
    else if (isOperator(element))
    {
      while (!stack.isEmpty() && ((stack.drop() == "*") || (stack.drop() == "/") || (stack.drop() == "%")))
      {
        postfix.push(stack.drop());
        stack.pop();
      }
      stack.push(element);
    }
    else
    {
      throw std::logic_error("error");
    }
  }
  while (!stack.isEmpty())
  {
    postfix.push(stack.drop());
    stack.pop();
  }
}
