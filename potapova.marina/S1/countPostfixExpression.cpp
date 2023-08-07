#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include <limits>
#include <stdexcept>
#include "queue.h"
#include "stack.h"

std::int64_t max_int = INT64_MAX;
std::int64_t min_int = INT64_MIN;

bool isOverflowPlus(std::int64_t operand1, std::int64_t operand2)
{
  return operand1 > 0 && operand2 > 0 && operand2 > (max_int - operand1);
}
    
bool isOverflowMinus(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 < 0 && operand2 > 0 && operand1 < (min_int + operand2));
}

bool isOverflowMultiply(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 > max_int / operand2) && ((operand1 > 0 && operand2 > 0) || (operand1 < 0 && operand2 < 0));
}

bool isOverflowDivision(std::int64_t operand1, std::int64_t operand2)
{
  return (operand1 < min_int / operand2) && ((operand1 > 0 && operand2 < 0) || (operand1 < 0 && operand2 > 0));
}

void pushWithCheckOverflow(potapova::Stack< std::int64_t > operands_stack, std::int64_t operand1, std::int64_t operand2, potapova::expr_queue& postfix_queue)
{
  if (isOverflowFunc(operand1, operand2)) 
  {
    throw std::overflow_error("Overflow while calculate");
  }
  else
  {
    operands_stack.push();
  }
}

bool (*isOverflowFunc)(std::int64_t operand1, std::int64_t operand2);

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
      //bool (*isOverflowFunc)(int64_t operand1, int64_t operand2);
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
          isOverflowFunc = isOverflowPlus;
          operands_stack.push(operand1 + operand2);
          break;
        case '-':
          isOverflowFunc = isOverflowMinus;
          operands_stack.push(operand1 - operand2);
          break;
        case '*':
          isOverflowFunc = isOverflowMultiply;
          operands_stack.push(operand1 * operand2);
          break;
        case '/':
          if (operand2 == 0)
          {
            throw std::runtime_error("Division by zero");
          }
          isOverflowFunc = isOverflowDivision;
          operands_stack.push(operand1 / operand2);
          break;
        case '%':
          operands_stack.push(operand1 % operand2);
          break;
      }
      /*if (isOverflowFunc(operand1, operand2)) 
      {
        throw std::overflow_error("Overflow while calculate");
      }*/
      postfix_queue.pop();
    }
  }
  return operands_stack.back();
}
