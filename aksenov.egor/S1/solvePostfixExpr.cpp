#include "solvePostfixExpr.h"
#include <stdexcept>
#include "mathOperations.h"
#include "queue.h"
#include "stack.h"
#include "details.h"

long long aksenov::solvePostfixExpr(Queue< std::string > &queue)
{
  Stack< long long > stack;
  while (!queue.isEmpty())
  {
    std::string elem = queue.get();
    queue.pop();

    if (isNumeric(elem))
    {
      stack.push(std::stoll(elem));
    }
    else if (isOperator(elem))
    {
      if (stack.isEmpty() || stack.size() < 2)
      {
        throw std::invalid_argument("Invalid postfix expression");
      }

      long long operand2 = stack.get();
      stack.pop();

      long long operand1 = stack.get();
      stack.pop();

      long long result = 0;

      if (elem == "+")
      {
        result = sum(operand1, operand2);
      }
      else if (elem == "-")
      {
        result = substract(operand1, operand2);
      }
      else if (elem == "*")
      {
        result = multiply(operand1, operand2);
      }
      else if (elem == "/")
      {
        result = divide(operand1, operand2);
      }
      else if (elem == "%")
      {
        result = remaind(operand1, operand2);
      }
      stack.push(result);
    }
    else
    {
      throw std::invalid_argument("Invalid input");
    }
  }
  long long outRes = stack.get();
  if (stack.isEmpty() || stack.size() > 1)
  {
    throw std::invalid_argument("Invalid postfix expression");
  }
  return outRes;
}
