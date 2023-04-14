#ifndef MATHNODE_HPP
#define MATHNODE_HPP

#include <string>

#include "Operator.hpp"

namespace odintsov {
  class MathNode {
   public:
    enum class Tag {
      Operand,
      Operator,
      OpenParen,
      CloseParen
    };

    MathNode(long long operand);
    MathNode(const odintsov::Operator& oper);
    MathNode(char paren);
    MathNode(const std::string& str);

    Tag getTag() const;

    long long getOperand() const;
    odintsov::Operator& getOperator();
    const odintsov::Operator& getOperator() const;

   private:
    Tag tag_;

    union Data {
      long long operand;
      odintsov::Operator oper;
    } data_;
  };
}

#endif
