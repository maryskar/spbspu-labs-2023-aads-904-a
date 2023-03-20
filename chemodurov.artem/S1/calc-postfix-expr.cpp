#include "calc-postfix-expr.hpp"
#include "stack.hpp"
#include "overflows-of-long.hpp"

long chemodurov::calcPostfixExpr(Queue< PostfixExpr > & post)
{
  Stack< long > calc;
  while (!post.empty())
  {
    PostfixExpr next = post.getFromQueue();
    if (next.isOperand)
    {
      calc.push(next.data.operand);
    }
    else
    {
      long rhs = calc.getFromStack();
      calc.pop();
      long lhs = calc.getFromStack();
      calc.pop();
      if (next.data.operation == OPERATION_PLUS)
      {
        calc.push(calcSum(lhs, rhs));
      }
      else if (next.data.operation == OPERATION_MINUS)
      {
        calc.push(calcDiff(lhs, rhs));
      }
      else if (next.data.operation == OPERATION_MULTIPLICATION)
      {
        calc.push(calcMultiplication(lhs, rhs));
      }
      else if (next.data.operation == OPERATION_DIVIDE)
      {
        calc.push(calcDivision(lhs, rhs));
      }
      else if (next.data.operation == OPERATION_REMINDER_OF_DIVISION)
      {
        calc.push(lhs % rhs);
      }
      else
      {
        throw std::invalid_argument("Wrong operation");
      }
    }
    post.pop();
  }
  long res = calc.getFromStack();
  calc.pop();
  if (!calc.empty())
  {
    throw std::invalid_argument("Wrong expression");
  }
  return res;
}
