#include "postfix_prefix.h"
#include "calculator.h"

Queue< std::string > operation::makeInfix(std::string string)
{
  Queue< std::string > infix_queue;
  size_t infix_size = 0;
  while (string.size() != infix_size)
  {
    std::string token = "";
    while (string.size() < infix_size && !std::isspace(string[infix_size]))
    {
      infix_queue.push(string[i]);
      token += string[i];
      infix_size++;
    }
    infix_size++;
  }
  return infix_queue;
}


Queue< std::string > infixToPostfix(Queue<std::string>& infix_queue)
{
  Queue<std::string> postfix_queue;
  Stack<std::string> operator_stack;

  while (!infix_queue.isEmpty())
  {
    std::string token = infix_queue.get();
    infix_queue.pop();

    if (isOperator(token))
    {
      while (!operator_stack.isEmpty() && hasHigherPrecedence(operator_stack.get(), token))
      {
        postfix_queue.push(operator_stack.get());
        operator_stack.pop();
      }
      operator_stack.push(token);
    }
    else if (isOperand(token))
    {
      postfix_queue.push(token);
    }
    else if (token == "(")
    {
      operator_stack.push(token);
    }
    else if (token == ")")
    {
      while (!operator_stack.isEmpty() && operator_stack.get() != "(")
      {
        postfix_queue.push(operator_stack.get());
        operator_stack.pop();
      }
      operator_stack.pop();
    }
  }

  while (!operator_stack.isEmpty())
  {
    postfix_queue.push(operator_stack.get());
    operator_stack.pop();
  }

  return postfix_queue;
}
