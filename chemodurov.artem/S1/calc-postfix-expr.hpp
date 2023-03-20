#ifndef CALC_POSTFIX_EXPR_HPP
#define CALC_POSTFIX_EXPR_HPP
#include "postfix-expr.hpp"
#include "queue.hpp"

namespace chemodurov
{
  int calcPostfixExpr(Queue< PostfixExpr > & post);
}

#endif
