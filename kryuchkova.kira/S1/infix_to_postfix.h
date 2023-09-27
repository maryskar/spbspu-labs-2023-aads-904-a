#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX
#include "queue.h"
#include "part_of_exp.h"

namespace kryuchkova
{
  Queue< ExpressionMember > getPostfixExp(Queue< ExpressionMember > &inf);
}

#endif
