#ifndef READ_INFIX_EXPR_HPP
#define READ_INFIX_EXPR_HPP
#include <iosfwd>
#include "infix-expression.hpp"

namespace chemodurov
{
  InfixExpr * readInfixExpr(std::string & line, size_t & inf_size);
}

#endif
