#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"

chemodurov::Queue< chemodurov::PostfixExpr > chemodurov::convertInfixToPostfix(Queue< InfixExpr > inf)
{
  Queue< PostfixExpr > post;
  Stack< OperationAndBrace > stack;
  InfixExpr next = inf.getFromQueue();
  if (next.isOperand)
  {
    PostfixExpr temp = {next.data.operand, true};
    post.push(temp);
  }
  //
  return post;
}
