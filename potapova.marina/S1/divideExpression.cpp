#include "divideExpression.h"
#include <stdexcept>
#include "stack.h"

size_t getPriority(const char operation)
{
  if (operation == '*' || operation == '/')
  {
    return 1;
  }
  return 0;
}

bool isOpenBracket(const char value)
{
  return (value == '(');
}

bool isCloseBracket(const char value)
{
  return value == ')';
}

void moveExprInBracketsToPostfix(potapova::Stack< char >& operators_stack,
                                 potapova::expr_queue& postfix_expr)
{
  while (!isOpenBracket(operators_stack.back()))
  {
    postfix_expr.push(potapova::ArithmExpMember(operators_stack.back()));
    operators_stack.pop();
    if (operators_stack.empty())
    {
      throw std::logic_error("Was found close bracket without open bracket");
    }
  }
  operators_stack.pop();
}

potapova::expr_queue potapova::composePostfixQueue(expr_queue& infix_expr)
{
  expr_queue postfix_expr;
  Stack< char > operators_stack;
  while (!infix_expr.empty())
  {
    ArithmExpMember& cur_member = infix_expr.front();
    if (cur_member.type == ArithmExpMember::Type::Num)
    {
      postfix_expr.push(cur_member);
    }
    else if (isOpenBracket(cur_member.operation || operators_stack.empty() || isOpenBracket(operators_stack.back())))
    {
      operators_stack.push(cur_member.operation);
    }
    else if (isCloseBracket(cur_member.operation))
    {
      moveExprInBracketsToPostfix(operators_stack, postfix_expr);
    }
    else if (getPriority(cur_member.operation) < getPriority(operators_stack.back()))
    {
      operators_stack.push(cur_member.operation);
    }
    else
    {
      postfix_expr.push(ArithmExpMember(operators_stack.back()));
      operators_stack.back() = cur_member.operation;
    }
    infix_expr.pop();
  }
  while (!operators_stack.empty())
  {
    postfix_expr.push(operators_stack.back());
    operators_stack.pop();
  }
  return postfix_expr;
}
