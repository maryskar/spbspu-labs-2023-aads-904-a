#include "calc-postfix-expr.hpp"
#include "stack.hpp"
#include "overflows-of-long.hpp"

long chemodurov::calcPostfixExpr(Queue< PostfixExpr > & post)
{
  Stack< long > calc;
  while (!post.empty())
  {
    PostfixExpr next = post.getFromQueue();
    if (next.isOperand())
    {
      calc.push(next.getOperand());
    }
    else
    {
      long rhs = calc.getFromStack();
      calc.pop();
      long lhs = calc.getFromStack();
      calc.pop();
      if (next.getOperation() == operation_t::PLUS)
      {
        calc.push(calcSum(lhs, rhs));
      }
      else if (next.getOperation() == operation_t::MINUS)
      {
        calc.push(calcDiff(lhs, rhs));
      }
      else if (next.getOperation() == operation_t::MULTIPLICATION)
      {
        calc.push(calcMultiplication(lhs, rhs));
      }
      else if (next.getOperation() == operation_t::DIVIDE)
      {
        calc.push(calcDivision(lhs, rhs));
      }
      else if (next.getOperation() == operation_t::REMINDER_OF_DIVISION)
      {
        calc.push(calcReminderOfDivision(lhs, rhs));
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
