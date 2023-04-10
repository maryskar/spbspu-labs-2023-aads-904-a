#include "MathSolver.hpp"

#include <functional>
#include <iostream>

void odintsov::MathSolver::operator()(const std::string& nodeStr)
{
  MathNode node(nodeStr);
  processParen(node);
  processOperand(node);
  processOperator(node);
}

long long odintsov::MathSolver::getResult()
{
  sendOperatorsOver();
  if (!opers_.empty()) {
    throw std::runtime_error("Syntax error");
  }
  Stack< MathNode > solver;
  while (!result_.empty()) {
    MathNode node = result_.head();
    if (node.isDataType(MathNode::Tag::Operator)) {
      long long rhs = solver.tail().getOperand();
      solver.pop();
      long long lhs = solver.tail().getOperand();
      solver.pop();
      long long res = node.getOperator().exec(lhs, rhs);
      solver.push(MathNode(res));
    } else {
      solver.push(result_.head());
    }
    result_.pop();
    std::cout << result_.empty() << '\n';
  }
  if (solver.empty()) {
    throw std::runtime_error("Empty expression");
  }
  long long res = solver.tail().getOperand();
  solver.pop();
  if (!solver.empty()) {
    throw std::runtime_error("Syntax error");
  }
  return res;
}

void odintsov::MathSolver::processParen(MathNode& paren)
{
  if (!paren.isDataType(MathNode::Tag::Paren)) {
    return;
  }
  if (paren.getParen() == '(') {
    opers_.push(paren);
  } else {
    sendOperatorsOver();
    if (opers_.empty()) {
      throw std::runtime_error("Parenthesis error");
    }
    MathNode openParen = opers_.tail();
    if (!openParen.isDataType(MathNode::Tag::Paren) || openParen.getParen() != '(') {
      throw std::runtime_error("Parenthesis error");
    }
    opers_.pop();
  }
}

void odintsov::MathSolver::processOperand(MathNode& operand)
{
  if (!operand.isDataType(MathNode::Tag::Operand)) {
    return;
  }
  result_.push(operand);
}

void odintsov::MathSolver::processOperator(MathNode& oper)
{
  if (!oper.isDataType(MathNode::Tag::Operator)) {
    return;
  }
  const Operator& operPriority = oper.getOperator();
  sendOperatorsOver([&operPriority](const Operator& stackOper) {
    return stackOper >= operPriority;
  });
  opers_.push(oper);
}

void odintsov::MathSolver::sendOperatorsOver()
{
  sendOperatorsOver([](const Operator&) {
    return true;
  });
}

void odintsov::MathSolver::sendOperatorsOver(std::function< bool(const Operator&) > confirmSend)
{
  while (!opers_.empty()) {
    MathNode oper = opers_.tail();
    if (!(oper.isDataType(MathNode::Tag::Operator) && confirmSend(oper.getOperator()))) {
      break;
    }
    result_.push(oper);
    opers_.pop();
  }
}

odintsov::MathSolver::MathNode::MathNode(long long operand):
  tag_(Tag::Operand),
  data_{.operand = operand}
{}

odintsov::MathSolver::MathNode::MathNode(const std::string& str):
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
  new (&data_.oper) Operator(c);
  tag_ = Tag::Operator;
}

odintsov::MathSolver::MathNode::~MathNode()
{
  if (tag_ == Tag::Operator) {
    data_.oper.~Operator();
  }
}

bool odintsov::MathSolver::MathNode::isDataType(Tag tag) const
{
  return tag_ == tag;
}

long long odintsov::MathSolver::MathNode::getOperand() const
{
  if (tag_ != Tag::Operand) {
    throw std::logic_error("Invalid attempt to interpret node as operand");
  }
  return data_.operand;
}

odintsov::Operator& odintsov::MathSolver::MathNode::getOperator()
{
  return const_cast< Operator& >(const_cast< const MathNode* >(this)->getOperator());
}

const odintsov::Operator& odintsov::MathSolver::MathNode::getOperator() const
{
  if (tag_ != Tag::Operator) {
    throw std::logic_error("Invalid attempt to interpret node as operator");
  }
  return data_.oper;
}

char odintsov::MathSolver::MathNode::getParen() const
{
  if (tag_ != Tag::Paren) {
    throw std::logic_error("Invalid attempt to interpret node as parenthesis");
  }
  return data_.paren;
}
