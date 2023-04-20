#include "PostfixNode.hpp"

#include <stdexcept>

#include "Operator.hpp"

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

odintsov::PostfixNode::Tag odintsov::PostfixNode::getTag() const
{
  return tag_;
}

bool odintsov::PostfixNode::isOperand() const
{
  return getTag() == Tag::Operand;
}

bool odintsov::PostfixNode::isOperator() const
{
  return getTag() == Tag::Operator;
}

long long odintsov::PostfixNode::getOperand() const
{
  if (!isOperand()) {
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
  if (!isOperator()) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return data_.oper;
}
