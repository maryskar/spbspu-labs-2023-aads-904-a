#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include "queue.h"
#include "stack.h"

constexpr std::int64_t MAX_INT = std::numeric_limits< std::int64_t >::max();
constexpr std::int64_t MIN_INT = std::numeric_limits< std::int64_t >::min();

bool isOverflowPlus(std::int64_t operand1, std::int64_t operand2)
{
  return operand1 > 0 && operand2 > 0 && operand2 > (MAX_INT - operand1);
}

bool isOverflowMinus(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 < 0 && operand2 > 0 && operand1 < (MIN_INT + operand2));
}

bool isOverflowMultiply(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 > MAX_INT / operand2);
}

bool isOverflowDivision(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 < MIN_INT / operand2) && ((operand1 > 0 && operand2 < 0) || (operand1 < 0 && operand2 > 0));
}

std::int64_t potapova::countPostfixExpression(expr_queue& postfix_queue)
{
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
          operands_stack.push(operand1 % operand2);
          break;
      }
      postfix_queue.pop();
    }
  }
  return operands_stack.back();
}
