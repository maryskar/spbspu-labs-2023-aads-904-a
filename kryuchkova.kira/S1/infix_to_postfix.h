#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX
#include "queue.h"
#include "part_of_exp.h"

namespace kryuchkova
{
  Queue< ExpressionMember > GetPostfixExp(Queue< ExpressionMember > & inf);
}

#endif
