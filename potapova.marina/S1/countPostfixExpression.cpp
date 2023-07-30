#include "countPostfixExpression.h"
#include <iostream>
#include <istream>
#include "queue.h"
#include "stack.h"

int potapova::countPostfixExpression(expr_queue& postfix_queue)
{
  Stack< int > operands_stack;
  while (!postfix_queue.empty())
  {
    if (postfix_queue.front().type == ArithmExpMember::Type::Num)
    {
      operands_stack.push(static_cast< int >(postfix_queue.front()));
      postfix_queue.pop();
    }
    else
    {
      int operand2 = operands_stack.back();
      operands_stack.pop();
      int operand1 = operands_stack.back();
      operands_stack.pop();
      switch (postfix_queue.front().operation)
      {
        case '+':
          operands_stack.push(operand1 + operand2);
          postfix_queue.pop();
          break;
        case '-':
          operands_stack.push(operand1 - operand2);
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
  return operands_stack.back();
}
