#include "postfix_prefix.h"
#include "calculator.h"
Queue< std::string > infixToPostfix(Queue<std::string>& infix_queue)
{
  Queue< std::string > postfix_queue;
  Stack< std::string > operator_stack;

  while (!infix_queue.isEmpty())
  {
    std::string token = infix_queue.dequeue();

    if (calculator::isOperation(token))
    {
      while (!operator_stack.empty() && calculator::isOperation(operator_stack.top()) &&
        getPrecedence(token) <= getPrecedence(operator_stack.top()))
      {
        postfix_queue.enqueue(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.push(token);
    }
    else if (token == "(")
    {
      operator_stack.push(token);
    }
    else if (token == ")")
    {
      while (!operator_stack.empty() && operator_stack.top() != "(")
      {
        postfix_queue.enqueue(operator_stack.top());
        operator_stack.pop();
      }
      operator_stack.pop();
    }
    else
    {
      postfix_queue.enqueue(token);
    }
  }

  while (!operator_stack.empty())
  {
    // postfix_queue.push(operator_stack.top());
    operator_stack.pop();
  }

  return postfix_queue;
}

Queue< std::string > operation::makePrefix(Queue< std::string >& infix_queue);

