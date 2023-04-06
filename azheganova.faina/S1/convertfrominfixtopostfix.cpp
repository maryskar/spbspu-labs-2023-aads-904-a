#include "convertfrominfixtopostfix.h"
#include <cctype>
#include <iostream>
#include "stack.h"
#include "operations.h"

bool isDigit(const std::string & str)
{
  std::stoll(str, nullptr, 10);
  return true;
}

bool isOperator(const std::string & oper)
{
  return (oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%");
}

bool checkPriority(const std::string & priority1, const std::string & priority2)
{
  getPriority(priority1);
  getPriority(priority2);
  return (priority1 >= priority2);
}

Queue< std::string > convertFromInfixToPostfix(Queue< std::string > queue)
{
  Queue< std::string > postfix;
  Stack< std::string > * stack = new Stack< std::string >;
  while (!queue.isEmpty())
  {
    std::string element = queue.pop();
    if (isDigit(element))
    {
      postfix.push(element);
    }
    else if (isOperator(element))
    {
      if (!stack->isEmpty())
      {
        if (checkPriority(element, stack->drop()))
        {
          postfix.push(stack->pop());
        }
      }
      stack->push(element);
    }
    else if (element == "(")
    {
      stack->push(element);
    }
    else if (element == ")")
    {
      while (stack->drop() != "(")
      {
        if (stack->isEmpty())
        {
          break;
        }
        postfix.push(stack->pop());
      }
      stack->pop();
    }
    else
    {
      while (!stack->isEmpty())
      {
        postfix.push(stack->pop());
      }
    }
  }
  delete stack;
  return postfix;
}
