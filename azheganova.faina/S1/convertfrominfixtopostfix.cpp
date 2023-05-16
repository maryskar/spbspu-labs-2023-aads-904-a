#include "convertfrominfixtopostfix.h"
#include <cctype>

bool azheganova::getPriority(std::string oper)
{
  if (oper == "+")
  {
    return 0;
  }
  else if (oper == "-")
  {
    return 0;
  }
  else if (oper == "*")
  {
    return 1;
  }
  else if (oper == "/")
  {
    return 1;
  }
  else if (oper == "%")
  {
    return 1;
  }
  else if (oper == ")")
  {
    return 2;
  }
  else if (oper == "(")
  {
    return 2;
  }
  else
  {
    throw std::logic_error("error");
  }
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
    else if (!getPriority(element))
    {
      while (!stack.isEmpty() && (!getPriority(stack.get()) > getPriority(element)))
      {
        postfix.push(stack.get());
        stack.pop();
      }
      stack.push(element);
    }
    else if (getPriority(element))
    {
      while (!stack.isEmpty() && (getPriority(stack.get()) > getPriority(element)))
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
