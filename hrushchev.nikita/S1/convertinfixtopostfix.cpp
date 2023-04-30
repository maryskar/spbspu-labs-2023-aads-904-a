#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

bool isHighPriorOperator(std::string op)
{
  return (op == "*") || (op == "/") || (op == "%");
}

bool isLowPriorOperator(std::string op)
{
  return  (op == "+") || (op == "-");
}

bool isOperator(std::string op)
{
  return isLowPriorOperator(op) || isHighPriorOperator(op);
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
    else if (isLowPriorOperator(token))
    {
      while (!stack.isEmpty() && isOperator(stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(token);
    }
    else if (isHighPriorOperator(token))
    {
      while (!stack.isEmpty() && isHighPriorOperator(stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(token);
    }
    else if (token == "(")
    {
      stack.push(token);
    }
    else if (token == ")")
    {
      while (!stack.isEmpty() && stack.get() != "(")
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }
  while (!stack.isEmpty())
  {
    postfixQueue.push(stack.get());
    stack.pop();
  }
  return postfixQueue;
}

