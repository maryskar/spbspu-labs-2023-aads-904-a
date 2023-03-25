#include "MathNode.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

odintsov::MathNode getMathNodeFromString(const std::string& str)
{
  try {
    return odintsov::MathNode(stod(str));
  } catch (const std::invalid_argument& e) {
  }
  if (str.size() != 1) {
    throw std::invalid_argument("Incorrect operator/operand");
  }
  char c = str[0];
  try {
    return odintsov::MathNode(c);
  } catch (const std::invalid_argument& e) {
  }
  return odintsov::MathNode(odintsov::Operator(c));
}

odintsov::MathNode::MathNode(double operand):
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
  MathNode(getMathNodeFromString(str))
{}
