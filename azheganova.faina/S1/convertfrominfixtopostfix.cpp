#include "convertfrominfixtopostfix.h"
#include <cctype>
#include <iostream>

bool isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
}

bool isDigit(const std::string & string)
{
  try
  {
    std::stoll(string, nullptr, 10);
  }
  catch(const std::exception & e)
  {
    return false;
  }
  return true;
}

void convertFromInfixToPostfix(Queue< std::string > & queue, Stack< std::string > & stack, Queue< std::string > & postfix)
{
  while (!queue.isEmpty() || !stack.isEmpty())
  {
    if (!queue.isEmpty())
    {
      std::string element = queue.drop();
      queue.pop();
      if (isDigit(element))
      {
        postfix.push(element);
      }
      if (isOperator(element))
      {
        if (element == "+" || element == "-")
        {
          while (!stack.isEmpty() && isOperator(stack.drop()))
          {
            postfix.push(stack.drop());
            stack.pop();
          }
          stack.push(element);
        }
        if (element == "*" || element == "/" || element == "%")
        {
          while (!stack.isEmpty() && ((stack.drop() == "*" || stack.drop() == "/" || stack.drop() == "%")))
          {
            postfix.push(stack.drop());
            stack.pop();
          }
          stack.push(element);
        }
      }
      if (element == "(")
      {
        stack.push(element);
      }
      if (element == ")")
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
    }
    else
    {
      while (!stack.isEmpty())
      {
        postfix.push(stack.drop());
        stack.pop();
      }
    }
  }
}
