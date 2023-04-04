#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"
#include "compare-operations-priority.hpp"

namespace chemodurov
{
  OperationAndBrace makeOperationAndBrace(Operation op)
  {
    OperationAndBrace temp;
    temp.isBrace = false;
    temp.data.operation = op;
    return temp;
  }
}

chemodurov::Queue< chemodurov::PostfixExpr > chemodurov::convertInfixToPostfix(Queue< InfixExpr > & inf)
{
  Queue< PostfixExpr > post;
  Stack< OperationAndBrace > stack;
  while (!inf.empty())
  {
    InfixExpr next = inf.getFromQueue();
    if (next.isOperand())
    {
      PostfixExpr temp(next.getOperand());
      post.push(temp);
    }
    else if (next.isBrace())
    {
      if (next.getBrace() == BRACE_LEFT)
      {
        stack.push({next.getBrace(), true});
      }
      else if (next.getBrace() == BRACE_RIGHT)
      {
        while (!stack.empty() && !stack.getFromStack().isBrace)
        {
          PostfixExpr temp(stack.getFromStack().data.operation);
          post.push(temp);
          stack.pop();
        }
        if (stack.empty())
        {
          throw std::invalid_argument("Incorrect infix expression");
        }
        stack.pop();
      }
    }
    else if (next.isOperation())
    {
      if (stack.empty())
      {
        stack.push(makeOperationAndBrace(next.getOperation()));
      }
      else
      {
        int prior_diff = compareOperationsPriority(next.getOperation(), stack.getFromStack().data.operation);
        while (!stack.empty() && !stack.getFromStack().isBrace && prior_diff >= 0)
        {
          PostfixExpr temp(stack.getFromStack().data.operation);
          post.push(temp);
          stack.pop();
          if (stack.empty())
          {
            break;
          }
          prior_diff = compareOperationsPriority(next.getOperation(), stack.getFromStack().data.operation);
        }
        stack.push(makeOperationAndBrace(next.getOperation()));
      }
    }
    inf.pop();
  }
  while (!stack.empty() && !stack.getFromStack().isBrace)
  {
    PostfixExpr temp(stack.getFromStack().data.operation);
    post.push(temp);
    stack.pop();
  }
  if (!stack.empty() && stack.getFromStack().isBrace)
  {
    throw std::invalid_argument("Wrong infix expression");
  }
  return post;
}
