#include "convertfrominfixtopostfix.h"
#include <cctype>
#include <iostream>
#include "checkingfordigit.h"

bool isOperator(std::string oper)
{
  return (oper == "+") || (oper == "-") || (oper == "*") || (oper == "/") || (oper == "%");
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
      else if (isOperator(element))
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
        else if (element == "*" || element == "/" || element == "%")
        {
          while (!stack.isEmpty() && ((stack.drop() == "*" || stack.drop() == "/" || stack.drop() == "%")))
          {
            postfix.push(stack.drop());
            stack.pop();
          }
          stack.push(element);
        }
      }
      else if (element == "(")
      {
        stack.push(element);
      }
      else if (element == ")")
      {
        while ((stack.drop() != "(") && (!stack.isEmpty()))
        {
          postfix.push(stack.drop());
          stack.pop();
        }
        stack.pop();
      }
      else
      {
        throw std::logic_error("error");
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
