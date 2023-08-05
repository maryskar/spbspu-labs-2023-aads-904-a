#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include "queue.h"
#include "stack.h"

bool checkOverflowPlus(std::int64_t operand1, std::int64_t operand2, std::int64_t max_int)
{
  return operand1 > 0 && operand2 > 0 && operand2 > (max_int - operand1);
}
    
bool checkOverflowMinus(std::int64_t operand1, std::int64_t operand2, std::int64_t min_int)
{
  return (operand1 < 0 && operand2 < 0 && operand1 < (min_int - operand2)) || (operand1 < 0 && operand2 > 0 && operand1 < (min_int + operand2)) || (operand1 > 0 && operand2 < 0 && operand1 < (min_int + operand2));
}

bool checkOverflowMultiply(std::int64_t operand1, std::int64_t operand2, std::int64_t max_int)
{
  return (operand1 > max_int / operand2) && ((operand1 > 0 && operand2 > 0) || (operand1 < 0 && operand2 < 0));
}

bool checkOverflowDivision(std::int64_t operand1, std::int64_t operand2, std::int64_t min_int)
{
  return (operand1 < min_int / operand2) && ((operand1 > 0 && operand2 < 0) || (operand1 < 0 && operand2 > 0));
}

bool isOverflowPlusMinus(std::int64_t operand1, std::int64_t operand2, std::int64_t max_int, std::int64_t min_int)
{
  return checkOverflowPlus(operand1, operand2, max_int) || checkOverflowMinus(operand1, operand2, min_int);
}

bool isOverflowMultiplyDivision(std::int64_t operand1, std::int64_t operand2, std::int64_t max_int, std::int64_t min_int)
{
  return checkOverflowMultiply(operand1, operand2, max_int) || checkOverflowDivision(operand1, operand2, min_int);
}

std::int64_t potapova::countPostfixExpression(expr_queue& postfix_queue)
{
  const std::int64_t max_int = std::numeric_limits< std::int64_t >::max();
  const std::int64_t min_int = std::numeric_limits< std::int64_t >::min();
  Stack< std::int64_t > operands_stack;
  while (!postfix_queue.empty())
  {
    if (postfix_queue.front().type == ArithmExpMember::Type::Num)
    {
      operands_stack.push(postfix_queue.front().num);
      postfix_queue.pop();
    }
    else
    {
      std::int64_t operand2 = operands_stack.back();
      operands_stack.pop();
      std::int64_t operand1 = operands_stack.back();
      operands_stack.pop();
      switch (postfix_queue.front().operation)
      {
        case '+':
          if (isOverflowPlusMinus(operand1, operand2, max_int, min_int))
          {
            throw std::overflow_error("Overflow for plus");
          }
          operands_stack.push(operand1 + operand2);
          break;
        case '-':
          if (isOverflowPlusMinus(operand1, operand2, max_int, min_int))
          {
            throw std::overflow_error("Overflow for minus");
          }
          operands_stack.push(operand1 - operand2);
          break;
        case '*':
          if (isOverflowMultiplyDivision(operand1, operand2, max_int, min_int))
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
          if (isOverflowMultiplyDivision(operand1, operand2, max_int, min_int))
          {
            throw std::overflow_error("Overflow for division");
          }
          operands_stack.push(operand1 / operand2);
          break;
        case '%':
          operands_stack.push(operand1 % operand2);
          break;
      }
      postfix_queue.pop();
    }
  }
  return operands_stack.back();
}
