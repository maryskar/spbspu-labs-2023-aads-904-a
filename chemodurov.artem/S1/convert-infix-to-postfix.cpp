#include "convert-infix-to-postfix.hpp"
#include "stack.hpp"
#include "compare-operations-priority.hpp"

namespace chemodurov
{
  struct OperationAndParenthesis
  {
    union OperationParenthesis
    {
      parenthesis_t parenthesis;
      operation_t operation;
    } data;
    bool isParenthesis;
  };

  OperationAndParenthesis makeOperationAndParenthesis(operation_t op)
  {
    OperationAndParenthesis temp;
    temp.isParenthesis = false;
    temp.data.operation = op;
    return temp;
  }
}

chemodurov::Queue< chemodurov::PostfixExpr > chemodurov::convertInfixToPostfix(Queue< InfixExpr > & inf)
{
  Queue< PostfixExpr > post;
  Stack< OperationAndParenthesis > stack;
  while (!inf.empty())
  {
    InfixExpr next = inf.getFromQueue();
    if (next.isOperand())
    {
      PostfixExpr temp(next.getOperand());
      post.push(temp);
    }
    else if (next.isParenthesis())
    {
      if (next.getParenthesis() == parenthesis_t::LEFT)
      {
        stack.push({next.getParenthesis(), true});
      }
      else if (next.getParenthesis() == parenthesis_t::RIGHT)
      {
        while (!stack.empty() && !stack.getFromStack().isParenthesis)
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
        stack.push(makeOperationAndParenthesis(next.getOperation()));
      }
      else
      {
        bool prior_diff = isLessPriority(stack.getFromStack().data.operation, next.getOperation());
        while (!stack.empty() && !stack.getFromStack().isParenthesis && !prior_diff)
        {
          PostfixExpr temp(stack.getFromStack().data.operation);
          post.push(temp);
          stack.pop();
          if (stack.empty())
          {
            break;
          }
          prior_diff = isLessPriority(stack.getFromStack().data.operation, next.getOperation());
        }
        stack.push(makeOperationAndParenthesis(next.getOperation()));
      }
    }
    inf.pop();
  }
  while (!stack.empty() && !stack.getFromStack().isParenthesis)
  {
    PostfixExpr temp(stack.getFromStack().data.operation);
    post.push(temp);
    stack.pop();
  }
  if (!stack.empty() && stack.getFromStack().isParenthesis)
  {
    throw std::invalid_argument("Wrong infix expression");
  }
  return post;
}
