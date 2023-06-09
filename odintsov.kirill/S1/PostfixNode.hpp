#ifndef POSTFIXNODE_HPP
#define POSTFIXNODE_HPP

#include "Operator.hpp"

namespace odintsov {
  class PostfixNode {
   public:
    enum class Tag {
      Operand,
      Operator
    };

    PostfixNode(const PostfixNode&) = default;
    PostfixNode(PostfixNode&&) = default;
    explicit PostfixNode(long long operand);
    explicit PostfixNode(const odintsov::Operator& oper);

    Tag getTag() const;
    bool isOperand() const;
    bool isOperator() const;

    long long getOperand() const;
    long long unsafeGetOperand() const;
    odintsov::Operator& getOperator();
    const odintsov::Operator& getOperator() const;
    odintsov::Operator& unsafeGetOperator();
    const odintsov::Operator& unsafeGetOperator() const;

   private:
    Tag tag_;

    union Data {
      long long operand;
      odintsov::Operator oper;
    } data_;
  };
}

#endif
