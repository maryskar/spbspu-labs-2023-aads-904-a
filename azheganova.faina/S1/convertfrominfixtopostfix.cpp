#include "convertfrominfixtopostfix.h"
#include <cctype>
#include <iostream>
#include "checkdigit.h"

bool isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
}

void convertFromInfixToPostfix(Queue< std::string > & queue, Stack< std::string > & stack, Queue< std::string > & postfix)
{
  while (!queue.isEmpty())
  {
    std::string element = queue.drop();
    queue.pop();
    if (isDigit(element))
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
    else if (element == "+" || element == "-")
    {
      while (!stack.isEmpty() && isOperator(stack.drop()))
      {
        postfix.push(stack.drop());
        stack.pop();
      }
      stack.push(element);
    }
    else if (element == "*" || element == "/" || element == "%")
    {
      while (!stack.isEmpty() && ((stack.drop() == "*" || stack.drop() == "/" || stack.drop() == "%")))
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
