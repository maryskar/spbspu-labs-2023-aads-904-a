#ifndef DIVIDEEXPRESSION_H
#define DIVIDEEXPRESSION_H

#include <cstddef>
#include <string>
#include "queue.h"
#include "valueType.h"

namespace potapova
{
  size_t checkPriority(char& operation);
  bool isOpenBracket(char value);
  bool isCloseBracket(char value);
  void removeBrackets(expr_stack& operators_stack, expr_queue& postfix_expr);
  void addInPostfixQueue(expr_queue& postfix_expr, potapova::ArithmExpMember member);
  expr_queue potapova::composePostfixQueue(expr_queue& infix_expr);
}

#endif
