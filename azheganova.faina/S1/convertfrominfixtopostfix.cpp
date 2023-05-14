#include "convertfrominfixtopostfix.h"
#include <cctype>

bool azheganova::isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
}

void azheganova::convertFromInfixToPostfix(queue_str & queue, stack_str & stack, queue_str & postfix)
{
  while (!queue.isEmpty())
  {
    std::string element = queue.get();
    queue.pop();
    if (std::isdigit(element[0]))
    {
      postfix.push(element);
    }
    else if (element == "(")
    {
      stack.push(element);
    }
    else if (element == ")")
    {
      while (stack.get() != "(")
      {
        postfix.push(stack.get());
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
      while (!stack.isEmpty() && (isOperator(stack.get())))
      {
        postfix.push(stack.get());
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
    postfix.push(stack.get());
    stack.pop();
  }
}
