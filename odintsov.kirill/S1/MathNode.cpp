#include "MathNode.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

odintsov::MathNode::MathNode(long long operand):
  tag(Tag::Operand),
  data{.operand = operand}
{}

odintsov::MathNode::MathNode(const odintsov::Operator& oper):
  tag(Tag::Operator),
  data{.oper = oper}
{}

odintsov::MathNode::MathNode(char paren):
  tag(Tag::Paren),
  data{.paren = paren}
{
  if (paren != '(' && paren != ')') {
    throw std::invalid_argument("Incorrect parenthesis");
  }
}

odintsov::MathNode::MathNode(const std::string& str):
  data{0}
{
  try {
    data.operand = stoll(str);
    tag = Tag::Operand;
    return;
  } catch (const std::invalid_argument& e) {
  }
  if (str.size() != 1) {
    throw std::invalid_argument("Incorrect operator/operand");
  }
  char c = str[0];
  if (c == '(' || c == ')') {
    data.paren = c;
    tag = Tag::Paren;
    return;
  }
  data.oper = std::move(odintsov::Operator(c));
  tag = Tag::Operator;
}
