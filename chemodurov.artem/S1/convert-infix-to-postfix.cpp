#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"

chemodurov::Queue< chemodurov::PostfixExpr > chemodurov::convertInfixToPostfix(Queue< InfixExpr > inf)
{
  Queue< PostfixExpr > post;
  Stack< OperationAndBrace > stack;
  InfixExpr next = inf.getFromQueue();
  if (next.isOperand)
  {
    post.push({next.data.operand, true});
    inf.pop();
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
      inf.pop();
    }
  }
  //
  return post;
}
