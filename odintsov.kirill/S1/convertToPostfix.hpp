#ifndef CONVERTTOPOSTFIX_HPP
#define CONVERTTOPOSTFIX_HPP

#include "MathNode.hpp"
#include "Queue.hpp"

namespace odintsov {
  Queue< MathNode > convertToPostfix(const Queue< MathNode >& infixQueue);
}

#endif
