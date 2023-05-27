#ifndef SOLVEPOSTFIXEXPR_HPP
#define SOLVEPOSTFIXEXPR_HPP

#include "PostfixNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  long long solvePostfixExpr(Queue< PostfixNode > expr);
}

#endif
