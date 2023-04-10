#include "MathSolver.hpp"

#include <functional>

void odintsov::MathSolver::operator()(MathNode& node)
{
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
