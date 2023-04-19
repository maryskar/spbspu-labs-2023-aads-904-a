#include "MathNode.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

odintsov::MathNode::MathNode(const MathNode& n):
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

odintsov::MathNode::MathNode(MathNode&& n):
  tag_(n.tag_),
  data_(n.data_)
{
  n.data_.operand = 0;
}

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

odintsov::MathNode::MathNode(const std::string& str):
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
