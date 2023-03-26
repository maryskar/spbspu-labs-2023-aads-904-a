#ifndef MATHNODE_HPP
#define MATHNODE_HPP

#include <initializer_list>
#include <iosfwd>
#include <string>

#include "Operator.hpp"

namespace odintsov {
  struct MathNode {
    enum Tag {
      Operand,
      Operator,
      Paren
    } tag;

    union Data {
      long long operand;
      odintsov::Operator oper;
      char paren;
    } data;

    MathNode(long long operand);
    MathNode(const odintsov::Operator& oper);
    MathNode(char paren);
    MathNode(const std::string& str);
  };
}

#endif
