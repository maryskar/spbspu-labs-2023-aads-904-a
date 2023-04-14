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
  tag_(paren == '(' ? Tag::OpenParen : Tag::CloseParen),
  data_{0}
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
  if (c == '(') {
    tag_ = Tag::OpenParen;
    return;
  } else if (c == ')') {
    tag_ = Tag::CloseParen;
    return;
  }
  new (&data_.oper) odintsov::Operator(c);
  tag_ = Tag::Operator;
}

odintsov::MathNode::Tag odintsov::MathNode::getTag() const
{
  return tag_;
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
