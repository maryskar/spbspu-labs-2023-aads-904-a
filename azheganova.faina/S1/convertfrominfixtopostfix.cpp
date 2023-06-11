#include "convertfrominfixtopostfix.h"
#include <cctype>
#include "priority.h"
#include "stack.h"

bool isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
}

azheganova::Queue< std::string > azheganova::convertFromInfixToPostfix(Queue< std::string > & queue)
{
  Stack< std::string > stack;
  Queue< std::string > postfix;
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
      while (!stack.isEmpty() && (isLessPriority(stack.get(), element)))
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
  return postfix;
}
