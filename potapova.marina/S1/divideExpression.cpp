#include "divideExpression.h"
#include "inputInfixQueue.h"
#include "stack.h"

size_t potapova::checkPriority(char& operation)
{
  if (operation == '*' || operation == '/')
  {
    return 1;
  }
  return 0;
}

bool potapova::isOpenBracket(char value)
{
  return (value == '(');
}

bool potapova::isCloseBracket(char value)
{
  return (value == ')');
}

void potapova::removeBrackets(expr_stack& operators_stack, expr_queue& postfix_expr)
{
  while (!operators_stack.empty() && !potapova::isOpenBracket(operators_stack.back()))
  {
    potapova::ArithmExpMember member = operators_stack.back();
    operators_stack.pop();
    potapova::addInPostfixQueue(postfix_expr, member);
  }
}

void addInPostfixQueue(expr_queue& postfix_expr, potapova::ArithmExpMember member)
{
  
}

expr_queue potapova::composePostfixQueue(expr_queue& infix_expr)
{
  expr_queue postfix_expr;
  expr_stack operators_stack;
  while (!infix_expr.empty())
  {
    potapova::ArithmExpMember& cur_member = infix_expr.front();
    if (cur_member.type == potapova::ArithmExpMember::Type::Num)
    {
      postfix_expr.push(cur_member);
    }
    else if (cur_member.type == potapova::ArithmExpMember::Type::Operation)
    {
      if (isOpenBracket(cur_member.operation))
      {
        operators_stack.push(cur_member);
      }
      else if (isCloseBracket(cur_member.operation))
      {
        
      }
      operators_stack.push(cur_member);
    }
    infix_expr.pop();
  }
}
