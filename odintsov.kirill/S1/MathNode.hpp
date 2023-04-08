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
      Paren
    };

    MathNode(long long operand);
    MathNode(const odintsov::Operator& oper);
    MathNode(char paren);
    MathNode(const std::string& str);
    ~MathNode();

    bool isDataType(Tag tag) const;

    long long getOperand() const;
    odintsov::Operator& getOperator();
    const odintsov::Operator& getOperator() const;
    char getParen() const;

   private:
    Tag tag_;

    union Data {
      long long operand;
      odintsov::Operator oper;
      char paren;
    } data_;
  };
}

#endif
