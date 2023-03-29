#include "MathNode.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

odintsov::MathNode::MathNode(long long operand):
  tag_(Tag::Operand),
  data_{.operand = operand}
{}

odintsov::MathNode::MathNode(const odintsov::Operator& oper):
  tag_(Tag::Operator),
  data_{.oper = oper}
{}

odintsov::MathNode::MathNode(char paren):
  tag_(Tag::Paren),
  data_{.paren = paren}
{
  if (paren != '(' && paren != ')') {
    throw std::invalid_argument("Incorrect parenthesis");
  }
}

odintsov::MathNode::MathNode(const std::string& str):
  data_{0}
{
  try {
    data_.operand = stoll(str);
    tag_ = Tag::Operand;
    return;
  } catch (const std::invalid_argument& e) {
  }
  if (str.size() != 1) {
    throw std::invalid_argument("Incorrect operator/operand");
  }
  char c = str[0];
  if (c == '(' || c == ')') {
    data_.paren = c;
    tag_ = Tag::Paren;
    return;
  }
  data_.oper = std::move(odintsov::Operator(c));
  tag_ = Tag::Operator;
}

bool odintsov::MathNode::isDataType(Tag tag) const
{
  return tag_ == tag;
}

long long odintsov::MathNode::getOperand() const
{
  if (tag_ != Tag::Operand) {
    throw std::logic_error("Invalid attempt to interpret node as operand");
  }
  return data_.operand;
}

odintsov::Operator& odintsov::MathNode::getOperator()
{
  return const_cast< odintsov::Operator& >(const_cast< const odintsov::MathNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::MathNode::getOperator() const
{
  if (tag_ != Tag::Operator) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return data_.oper;
}

char odintsov::MathNode::getParen() const
{
  if (tag_ != Tag::Paren) {
    throw std::logic_error("Invalid attempt to interpret node as parenthesis");
  }
  return data_.paren;
}
