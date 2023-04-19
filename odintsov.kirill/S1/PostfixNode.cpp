#include "PostfixNode.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

namespace {
  bool isNumeric(const std::string& str)
  {
    if (str.empty()) {
      return false;
    }
    std::string::const_iterator c = str.begin();
    if (*c == '-') {
      c++;
    }
    while (c != str.end() && std::isdigit(*c)) {
      c++;
    }
    return c == str.end();
  }
}

odintsov::PostfixNode::PostfixNode(const PostfixNode& n):
  tag_(n.tag_),
  data_{0}
{
  switch (tag_) {
  case Tag::Operand:
    data_.operand = n.data_.operand;
    break;
  case Tag::Operator:
    new (&data_.oper) odintsov::Operator(n.data_.oper);
    break;
  default:
    break;
  }
}

odintsov::PostfixNode::PostfixNode(PostfixNode&& n):
  tag_(n.tag_),
  data_(n.data_)
{
  n.data_.operand = 0;
}

odintsov::PostfixNode::PostfixNode(long long operand):
  tag_(Tag::Operand),
  data_{.operand = operand}
{}

odintsov::PostfixNode::PostfixNode(const odintsov::Operator& oper):
  tag_(Tag::Operator),
  data_{.oper = oper}
{}

odintsov::PostfixNode::PostfixNode(const std::string& str):
  data_{0}
{
  if (isNumeric(str)) {
    data_.operand = stoll(str);
    tag_ = Tag::Operand;
    return;
  }
  if (str.size() != 1) {
    throw std::invalid_argument("Incorrect operator/operand");
  }
  new (&data_.oper) odintsov::Operator(str[0]);
  tag_ = Tag::Operator;
}

odintsov::PostfixNode::Tag odintsov::PostfixNode::getTag() const
{
  return tag_;
}

long long odintsov::PostfixNode::getOperand() const
{
  if (tag_ != Tag::Operand) {
    throw std::logic_error("Invalid attempt to interpret node as operand");
  }
  return data_.operand;
}

odintsov::Operator& odintsov::PostfixNode::getOperator()
{
  return const_cast< odintsov::Operator& >(const_cast< const odintsov::PostfixNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::PostfixNode::getOperator() const
{
  if (tag_ != Tag::Operator) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return data_.oper;
}
