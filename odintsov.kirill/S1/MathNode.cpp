#include "MathNode.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Operator.hpp"

odintsov::MathNode getOperand(double d)
{
  odintsov::MathNode::Tag tag = odintsov::MathNode::Tag::Operand;
  odintsov::MathNode::Data data{.operand = d};
  return odintsov::MathNode(tag, data);
}

odintsov::MathNode getOperator(char c)
{
  odintsov::MathNode::Tag tag = odintsov::MathNode::Tag::Operator;
  odintsov::MathNode::Data data{.oper = odintsov::Operator(c)};
  return odintsov::MathNode(tag, data);
}

odintsov::MathNode getParen(char c)
{
  if (c != '(' && c != ')') {
    throw std::invalid_argument("Incorrect parenthesis");
  }
  odintsov::MathNode::Tag tag = odintsov::MathNode::Tag::Paren;
  odintsov::MathNode::Data data{.paren = c};
  return odintsov::MathNode(tag, data);
}

odintsov::MathNode getMathNodeFromString(const std::string& str)
{
  try {
    return getOperand(stod(str));
  } catch (const std::invalid_argument& e) {
  }
  if (str.size() != 1) {
    throw std::invalid_argument("Unknown operator/operand");
  }
  char c = str[0];
  try {
    return getParen(c);
  } catch (const std::invalid_argument& e) {
  }
  return getOperator(c);
}

odintsov::MathNode getMathNodeFromStream(std::istream& in)
{
  std::string data;
  in >> data;
  if (!in) {
    throw std::runtime_error("Input error");
  }
  return getMathNodeFromString(data);
}

odintsov::MathNode::MathNode(Tag& t, Data& d):
  tag(t),
  data(d)
{}

odintsov::MathNode::MathNode(const std::string& str):
  MathNode(getMathNodeFromString(str))
{}

odintsov::MathNode::MathNode(std::istream& in):
  MathNode(getMathNodeFromStream(in))
{}
