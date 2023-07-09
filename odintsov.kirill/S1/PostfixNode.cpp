#include "PostfixNode.hpp"

#include <stdexcept>

#include "Operator.hpp"

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
  return unsafeGetOperand();
}

long long odintsov::PostfixNode::unsafeGetOperand() const
{
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
  return unsafeGetOperator();
}

odintsov::Operator& odintsov::PostfixNode::unsafeGetOperator()
{
  return const_cast< odintsov::Operator& >(const_cast< const odintsov::PostfixNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::PostfixNode::unsafeGetOperator() const
{
  return data_.oper;
}
