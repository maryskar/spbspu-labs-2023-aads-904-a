#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include <avltree.hpp>
#include "queue.hpp"
#include "stack.hpp"

namespace hrushchev
{
  int getOperatorPriority(const std::string& op)
  {
    if (op == "*" || op == "/" || op == "%" || op == "sin" || op == "cos")
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
    {
      throw std::logic_error("Invalid operator");
    }
  }

  bool isHigherPriority(const std::string& op1, const std::string& op2)
  {
    return getOperatorPriority(op1) >= getOperatorPriority(op2);
  }

  bool isOperator(const std::string& op)
  {
    return op == "*" || op == "/" || op == "+" || op == "-" || op == "(" || op == ")" || op == "%";
  }

  bool isUnaryOperator(const std::string& op)
  {
    return op == "sin" || op == "cos";
  }

  bool isVariable(const std::string& op, AVLTree< std::string, std::string >& variables)
  {
    try
    {
      variables.at(op);
      return true;
    }
    catch(...)
    {
      return false;
    }
  }
}

hrushchev::Queue< std::string > hrushchev::convertInfixToPostfix(Queue< std::string >& infixQueue,
    AVLTree< std::string, std::string >& variables)
{
  namespace hrn = hrushchev;
  hrn::Queue< std::string > postfixQueue;
  hrn::Stack< std::string > stack;

  while (!infixQueue.isEmpty())
  {
    std::string token = infixQueue.get();
    infixQueue.pop();
    if (std::isdigit(token[0]))
    {
      postfixQueue.push(token);
    }
    else if (hrn::isOperator(token))
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
      else if (token == "(")
      {
        stack.push(token);
      }
      else
      {
        while (!stack.isEmpty() && (hrn::isHigherPriority(stack.get(),token)))
        {
          postfixQueue.push(stack.get());
          stack.pop();
        }
        stack.push(token);
      }
    }
    else if (isUnaryOperator(token))
    {
      stack.push(token);
    }
    else if (isVariable(token, variables))
    {
      stack.push(variables.at(token));
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
