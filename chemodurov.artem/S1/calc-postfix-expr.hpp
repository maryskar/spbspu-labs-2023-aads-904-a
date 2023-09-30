#ifndef CALC_POSTFIX_EXPR_HPP
#define CALC_POSTFIX_EXPR_HPP
#include "postfix-expression.hpp"
#include "queue.hpp"

namespace chemodurov
{
  long calcPostfixExpr(Queue< PostfixExpr > & post);
}

#endif
