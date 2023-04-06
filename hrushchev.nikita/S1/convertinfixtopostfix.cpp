#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

bool isOperator(std::string op)
{
  return (op == "+") || (op == "-") || (op == "*") || (op == "/") || (op == "%");
}

Queue< std::string > convertInfixToPostfix(Queue< std::string >& infixQueue)
{
  Queue< std::string > postfixQueue;
  Stack< std::string > stack;
  while (!infixQueue.isEmpty())
  {
    std::string token = infixQueue.get();
    infixQueue.pop();
    if (std::isdigit(token[0]))
    {
      postfixQueue.push(token);
    }
    else if (token == "+" || token == "-")
    {
      while (!stack.isEmpty() && isOperator(stack.get()))
      {
        postfixQueue.push(stack.get());
        stack.pop();
      }
      stack.push(token);
    }
    else if (token == "*" || token == "/" || token == "%")
    {
      while (!stack.isEmpty() && ((stack.get() == "*" || stack.get() == "/" || stack.get() == "%")))
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

