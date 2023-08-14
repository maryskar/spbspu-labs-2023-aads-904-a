#include "divideExpression.h"
#include <stdexcept>
#include "stack.h"

namespace
{
  size_t getPriority(const char operation)
  {
    if (operation == '*' || operation == '/' || operation == '%')
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
}

potapova::expr_queue potapova::composePostfixQueue(expr_queue& infix_expr)
{
  expr_queue postfix_expr;
  Stack< char > operators_stack;
  Stack< char > brackets_stack;
  while (!infix_expr.empty())
  {
    ArithmExpMember& cur_member = infix_expr.front();
    if (cur_member.type == ArithmExpMember::Type::Num)
    {
      postfix_expr.push(cur_member);
    }
    else if (isCloseBracket(cur_member.operation))
    {
      if (brackets_stack.empty() || brackets_stack.back() != '(')
      {
        throw std::runtime_error("Inappropriate closing bracket");
      }
      brackets_stack.pop();
      moveExprInBracketsToPostfix(operators_stack, postfix_expr);
    }
    else if (isOpenBracket(cur_member.operation) || operators_stack.empty() || isOpenBracket(operators_stack.back()))
    {
      if (isOpenBracket(cur_member.operation))
      {
        brackets_stack.push(cur_member.operation);
      }
      operators_stack.push(cur_member.operation);
    }
    else if (!operators_stack.empty() && getPriority(cur_member.operation) <= getPriority(operators_stack.back()))
    {
      postfix_expr.push(operators_stack.back());
      operators_stack.pop();
      operators_stack.push(cur_member.operation);
    }
    else
    {
      operators_stack.push(cur_member.operation);
    }
    infix_expr.pop();
  }
  if (!brackets_stack.empty())
  {
    throw std::runtime_error("Inappropriate opening bracket");
  }
  while (!operators_stack.empty())
  {
    postfix_expr.push(operators_stack.back());
    operators_stack.pop();
  }
  if (!operators_stack.empty())
  {
    throw std::runtime_error("Invalid expression");
  }
  return postfix_expr;
}
