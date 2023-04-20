#ifndef INFIXNODE_HPP
#define INFIXNODE_HPP

#include "PostfixNode.hpp"

namespace odintsov {
  class InfixNode {
   public:
    enum class Tag {
      Operand,
      Operator,
      OpenParen,
      CloseParen
    };

    InfixNode(const InfixNode& in);
    InfixNode(InfixNode&& in);
    explicit InfixNode(const PostfixNode& pn);
    explicit InfixNode(long long operand);
    explicit InfixNode(const odintsov::Operator& oper);
    explicit InfixNode(char paren);
    ~InfixNode();

    Tag getTag() const;

    long long getOperand() const;
    odintsov::Operator& getOperator();
    const odintsov::Operator& getOperator() const;

   private:
    struct Impl;
    Impl* pImpl_;
  };
}

#endif
