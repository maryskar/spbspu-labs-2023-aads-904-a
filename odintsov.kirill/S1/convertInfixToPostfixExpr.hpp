#ifndef CONVERTINFIXTOPOSTFIXEXPR_HPP
#define CONVERTINFIXTOPOSTFIXEXPR_HPP

#include "InfixNode.hpp"
#include "PostfixNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  odintsov::Queue< PostfixNode > convertInfixToPostfixExpr(Queue< InfixNode > expr);
}

#endif
