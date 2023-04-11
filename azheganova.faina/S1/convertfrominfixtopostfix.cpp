#include "convertfrominfixtopostfix.h"
#include <cctype>
#include <iostream>
#include "stack.h"


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

bool isOperator(const std::string & oper)
{
  return (oper == "+" || oper == "-" || oper == "*" || oper == "/" || oper == "%");
}

Queue< std::string > convertFromInfixToPostfix(Queue< std::string > queue)
{
  Queue< std::string > postfix;
  Stack< std::string > stack;
  while (!queue.isEmpty())
  {
    std::string element = queue.pop();
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
      while (stack.drop() != "(")
      {
        if (stack.isEmpty())
        {
          break;
        }
        postfix.push(stack.drop());
      }
      stack.pop();
    }
    else
    {
      while (!stack.isEmpty())
      {
        postfix.push(stack.pop());
      }
    }
  }
  return postfix;
}
