#include "solvePostfix.hpp"

#include "Node.hpp"
#include "Stack.hpp"

long long odintsov::solvePostfix(const Queue< MathNode >& expr)
{
  detail::ConstNodeIter< MathNode > iter = expr.cbegin();
  detail::ConstNodeIter< MathNode > end = expr.cend();
  Stack< MathNode > solver;
  while (iter != end) {
    const MathNode node = *iter;
    if (node.getTag() == MathNode::Tag::Operator) {
      long long rhs = solver.tail().getOperand();
      solver.pop();
      long long lhs = solver.tail().getOperand();
      solver.pop();
      long long res = node.getOperator().exec(lhs, rhs);
      solver.push(MathNode(res));
    } else {
      solver.push(node);
    }
    iter++;
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
