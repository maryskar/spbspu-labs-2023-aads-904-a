#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include "queue.h"
#include "stack.h"

bool checkOverflow(const std::int64_t& value, std::int64_t& added)
{
  return (std::numeric_limits< std::int64_t >::max() - added >= value);
}

std::int64_t potapova::countPostfixExpression(expr_queue& postfix_queue)
{
  Stack< std::int64_t > operands_stack;
  std::int64_t added = 0;
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
          operands_stack.push(operand1 + operand2);
          added += operand1 + operand2;
          postfix_queue.pop();
          break;
        case '-':
          operands_stack.push(operand1 - operand2);
          added += operand1 - operand2;
          postfix_queue.pop();
          break;
        case '*':
          operands_stack.push(operand1 * operand2);
          postfix_queue.pop();
          break;
        case '/':
          operands_stack.push(operand1 / operand2);
          postfix_queue.pop();
          break;
        case '%':
          operands_stack.push(operand1 % operand2);
          postfix_queue.pop();
          break;
      }
    }
  }
  if (!checkOverflow(operands_stack.back(), added))
  {
    throw std::overflow_error("Overflow");
  }
  else
  {
    return operands_stack.back();
  }
}
