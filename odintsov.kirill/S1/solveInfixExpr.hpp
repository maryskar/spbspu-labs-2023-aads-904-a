#ifndef SOLVEINFIXEXPR_HPP
#define SOLVEINFIXEXPR_HPP

#include <string>

#include "InfixNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  long long solveInfixExpr(Queue< InfixNode > expr);
  long long solveInfixExpr(const std::string& exprStr);
}

#endif
