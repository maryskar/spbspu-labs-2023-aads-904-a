#ifndef CONVERT_INFIX_TO_POSTFIX_HPP
#define CONVERT_INFIX_TO_POSTFIX_HPP
#include "queue.hpp"
#include "infix-expression.hpp"
#include "postfix-expression.hpp"

namespace chemodurov
{
  Queue< PostfixExpr > convertInfixToPostfix(Queue< InfixExpr > & inf);
}

#endif
