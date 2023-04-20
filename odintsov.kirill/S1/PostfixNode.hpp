#ifndef POSTFIXNODE_HPP
#define POSTFIXNODE_HPP

#include <string>

#include "Operator.hpp"

namespace odintsov {
  class PostfixNode {
   public:
    enum class Tag {
      Operand,
      Operator
    };

    PostfixNode(const PostfixNode& n);
    PostfixNode(PostfixNode&& n);
    explicit PostfixNode(long long operand);
    explicit PostfixNode(const odintsov::Operator& oper);
    PostfixNode(const std::string& str);

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
