#include "calculations.h"

bool isOperator(const std::string & operator)
{
  return (operator == "+" || operator == "-" || operator == "*" || operator == "/" || operator == "%");
}

bool checkPriority(const std::string & n1, const std::string & n2)
{
  getPriority(priority1(n1));
  getPriority(priority2(n2);)
  return (priority1 >= priority2);
}

string convertFromInfixToPostfix(Queue< std::string > queue)
{
  Queue< std::string > postfix;
  Stack< std::string > *stack = new Stack< std::string >;
  while (!queue.isEmpty())
  {
    std::string element = queue.pop();
    if (isdigit(element))
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
    else if (element == '(')
    {
      stack->push(element);
    }
    else if (element == ')')
    {
      while (stack->drop() != "(")
      {
        postfix.push(stack->pop());
      }
      if (stack->isEmpty())
      {
        stack->pop();
      }
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