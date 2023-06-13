#ifndef SOLVEPOSTFIXEXPR_H
#define SOLVEPOSTFIXEXPR_H
#include "queue.h"
#include "stack.h"
namespace aksenov {
  Stack< long long > solvePostfixExpr(Queue< std::string > &queue);
}
#endif
