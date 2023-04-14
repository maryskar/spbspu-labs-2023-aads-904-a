#include "solvePostfix.hpp"

#include "Stack.hpp"

long long odintsov::solvePostfix(const Queue< MathNode >& expr)
{
  Queue< MathNode > exprCopy(expr);
  Stack< MathNode > solver;
  while (!exprCopy.empty()) {
    MathNode node = exprCopy.head();
    if (node.getTag() == MathNode::Tag::Operator) {
      long long rhs = solver.tail().getOperand();
      solver.pop();
      long long lhs = solver.tail().getOperand();
      solver.pop();
      long long res = node.getOperator().exec(lhs, rhs);
      solver.push(MathNode(res));
    } else {
      solver.push(exprCopy.head());
    }
    exprCopy.pop();
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
