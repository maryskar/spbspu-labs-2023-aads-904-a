#ifndef SOLVEPOSTFIX_HPP
#define SOLVEPOSTFIX_HPP

#include "MathNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  long long solvePostfix(const Queue< MathNode >& expr);
}

#endif
