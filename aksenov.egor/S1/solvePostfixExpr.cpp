#include "solvePostfixExpr.h"
#include <stdexcept>
#include "mathOperations.h"
#include "queue.h"
#include "stack.h"
#include "details.h"

long long aksenov::solvePostfixExpr(aksenov::Queue<std::string>& queue)
{
  aksenov::Stack< long long > stack;

  while (!queue.isEmpty())
  {
    std::string elem = queue.drop();
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

      long long operand2 = stack.drop();
      stack.pop();

      long long operand1 = stack.drop();
      stack.pop();

      long long result = 0;

      if (elem == "+")
      {
        result = aksenov::sum(operand1, operand2);
      }
      else if (elem == "-")
      {
        result = aksenov::substract(operand1, operand2);
      }
      else if (elem == "*")
      {
        result = aksenov::multiply(operand1, operand2);
      }
      else if (elem == "/")
      {
        result = aksenov::divide(operand1, operand2);
      }
      else if (elem == "%")
      {
        result = aksenov::remaind(operand1, operand2);
      }
      stack.push(result);
    }
    else
    {
      throw std::invalid_argument("Invalid input");
    }
  }
  long long outRes = stack.drop();
  if (stack.isEmpty() || stack.size() > 1)
  {
    throw std::invalid_argument("Invalid postfix expression");
  }
  return outRes;
}
