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

potapova::Queue< potapova::ArithmExpMember >& potapova::composePostfixQueue(potapova::Queue< potapova::ArithmExpMember >& infix_expr)
{
  potapova::Queue< potapova::ArithmExpMember > postfix_expr;
  potapova::Stack< potapova::ArithmExpMember > operators_stack;
  for (size_t expr_ptr = 0; expr_ptr < infix_expr.size(); ++expr_ptr)
  {

  }
}
