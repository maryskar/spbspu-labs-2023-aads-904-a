#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include "queue.h"
#include "stack.h"

namespace
{
  constexpr long long MAX_INT = std::numeric_limits< long long >::max();
  constexpr long long MIN_INT = std::numeric_limits< long long >::min();

  bool isOverflowPlus(long long operand1, long long operand2)
  {
    return operand1 > 0 && operand2 > 0 && operand2 > (MAX_INT - operand1);
  }

  bool isOverflowMinus(long long operand1, long long operand2)
  {
    return (operand1 < 0 && operand2 > 0 && operand1 < (MIN_INT + operand2));
  }

  bool isOverflowMultiply(long long operand1, long long operand2)
  {
    return (operand1 > MAX_INT / operand2) || (operand2 > MAX_INT / operand1);
  }

  bool isOverflowDivision(long long operand1, long long operand2)
  {
    return (operand1 < MIN_INT / operand2) && ((operand1 > 0 && operand2 < 0) || (operand1 < 0 && operand2 > 0));
  }

}

long long potapova::countPostfixExpression(expr_queue& postfix_queue)
{
  Stack< long long > operands_stack;
  while (!postfix_queue.empty())
  {
    if (postfix_queue.front().type == ArithmExpMember::Type::Num)
    {
      operands_stack.push(postfix_queue.front().num);
      postfix_queue.pop();
    }
    else
    {
      long long operand2 = operands_stack.top();
      operands_stack.pop();
      long long operand1 = operands_stack.top();
      operands_stack.pop();
      if (postfix_queue.front().operation == '+' && operand2 < 0)
      {
        operand2 *= -1;
        postfix_queue.front().operation = '-';
      }
      if (postfix_queue.front().operation == '-' && operand2 < 0)
      {
        operand2 *= -1;
        postfix_queue.front().operation = '+';
      }
      switch (postfix_queue.front().operation)
      {
        case '+':
          if (isOverflowPlus(operand1, operand2))
          {
            throw std::overflow_error("Overflow for plus");
          }
          operands_stack.push(operand1 + operand2);
          break;
        case '-':
          if (isOverflowMinus(operand1, operand2))
          {
            throw std::overflow_error("Overflow for minus");
          }
          operands_stack.push(operand1 - operand2);
          break;
        case '*':
          if (isOverflowMultiply(operand1, operand2))
          {
            throw std::overflow_error("Overflow for multiply");
          }
          operands_stack.push(operand1 * operand2);
          break;
        case '/':
          if (operand2 == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          if (isOverflowDivision(operand1, operand2))
          {
            throw std::overflow_error("Overflow for division");
          }
          operands_stack.push(operand1 / operand2);
          break;
        case '%':
          if (operand1 < 0)
          {
            operands_stack.push((operand1 % operand2 + operand2) % operand2);
          }
          else
          {
            operands_stack.push(operand1 % operand2);
          }
          break;
      }
      postfix_queue.pop();
    }
  }
  return operands_stack.top();
}
