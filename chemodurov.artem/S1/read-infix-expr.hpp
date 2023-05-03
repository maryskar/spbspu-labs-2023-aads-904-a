#ifndef READ_INFIX_EXPR_HPP
#define READ_INFIX_EXPR_HPP
#include <iosfwd>
#include "infix-expression.hpp"
#include "queue.hpp"

namespace chemodurov
{
  Queue< InfixExpr > readInfixExpr(std::string & line);
}

#endif
