#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"
#include "compare-operations-priority.hpp"
namespace chemodurov
{
  chemodurov::OperationAndBrace makeOperationAndBrace(chemodurov::Operation op)
  {
    OperationAndBrace temp;
    temp.isBrace = false;
    temp.data.operation = op;
    return temp;
  }
}

chemodurov::Queue< chemodurov::PostfixExpr > chemodurov::convertInfixToPostfix(Queue< InfixExpr > inf)
{
  Queue< PostfixExpr > post;
  Stack< OperationAndBrace > stack;
  InfixExpr next = inf.getFromQueue();
  if (next.isOperand)
  {
    post.push({next.data.operand, true});
  }
  else if (!next.isOperand && !next.isOperation)
  {
    if (next.data.brace == BRACE_LEFT)
    {
      stack.push({next.data.brace, true});
    }
    else if (next.data.brace == BRACE_RIGHT)
    {
      while (!stack.empty() && !stack.getFromStack().isBrace)
      {
        post.push({stack.getFromStack().data.operation, false});
        stack.pop();
      }
      if (stack.empty())
      {
        throw std::invalid_argument("Incorrect infix expression");
      }
      stack.pop();
    }
  }
  else if (next.isOperation)
  {
    if (stack.empty())
    {
      stack.push(makeOperationAndBrace(next.data.operation));
    }
    else
    {
      int prior_diff = compareOperationsPriority(next.data.operation, stack.getFromStack().data.operation);
      while (!stack.empty() && !stack.getFromStack().isBrace && prior_diff >= 0)
      {
        post.push({stack.getFromStack().data.operation, false});
        stack.pop();
        prior_diff = compareOperationsPriority(next.data.operation, stack.getFromStack().data.operation);
      }

      stack.push(makeOperationAndBrace(next.data.operation));
    }
  }
  inf.pop();
  return post;
}
