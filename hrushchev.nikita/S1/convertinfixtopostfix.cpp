#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

int getOperatorPriority(std::string op)
{
  if (op == "*" || op == "/")
  {
    return 2;
  }
  else if (op == "+" || op == "-")
  {
    return 1;
  }
  else if (op == "(" || op == ")")
  {
    return 0;
  }
  else
    throw std::logic_error("Invalid operator");
}

bool isOperator(std::string op)
{
  return op == "*" || op == "/" || op == "+" || op == "-" || op == "(" || op == ")";
}

hrushchev::Queue< std::string > hrushchev::convertInfixToPostfix(hrushchev::Queue< std::string >& infixQueue)
{
  namespace hr = hrushchev;
  hr::Queue< std::string > postfixQueue;
  hr::Stack< std::string > stack;

  while (!infixQueue.isEmpty())
  {
    std::string token = infixQueue.get();
    infixQueue.pop();

    if (std::isdigit(token[0]))
    {
      postfixQueue.push(token);
    }
    else if (isOperator(token))
    {
      if (token == ")")
      {
        while (!stack.isEmpty() && (stack.get() != "("))
        {
          postfixQueue.push(stack.get());
          stack.pop();
        }
        if (stack.isEmpty())
        {
          throw std::logic_error("Mismatched parentheses");
        }
        stack.pop();
      }
      else
      {
        while (!stack.isEmpty() && (getOperatorPriority(stack.get()) >= getOperatorPriority(token)))
        {
          postfixQueue.push(stack.get());
          stack.pop();
        }
        stack.push(token);
      }
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }

  while (!stack.isEmpty())
  {
    std::string op = stack.get();
    stack.pop();
    if (op == "(")
    {
      throw std::logic_error("Mismatched parentheses");
    }
    postfixQueue.push(op);
  }

  return postfixQueue;
}


