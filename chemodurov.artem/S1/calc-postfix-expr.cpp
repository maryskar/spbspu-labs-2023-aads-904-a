#include "calc-postfix-expr.hpp"
#include "stack.hpp"

int chemodurov::calcPostfixExpr(Queue< PostfixExpr > post)
{
  Stack< int > calc;
  while (!post.empty())
  {
    PostfixExpr next = post.getFromQueue();
    if (next.isOperand)
    {
      calc.push(next.data.operand);
    }
    else
    {
      int rhs = calc.getFromStack();
      calc.pop();
      int lhs = calc.getFromStack();
      calc.pop();
      if (next.data.operation == OPERATION_PLUS)
      {
        calc.push(rhs + lhs);
      }
      else if (next.data.operation == OPERATION_MINUS)
      {
        calc.push(rhs - lhs);
      }
      else if (next.data.operation == OPERATION_MULTIPLICATION)
      {
        calc.push(rhs * lhs);
      }
      else if (next.data.operation == OPERATION_DIVIDE)
      {
        calc.push(rhs / lhs);
      }
      else if (next.data.operation == OPERATION_REMINDER_OF_DIVISION)
      {
        calc.push(rhs % lhs);
      }
      else
      {
        throw std::invalid_argument("Wrong operation");
      }
    }
    post.pop();
  }
  int res = calc.getFromStack();
  calc.pop();
  if (!calc.empty())
  {
    throw std::invalid_argument("Wrong expression");
  }
  return res;
}
