#include "solvePostfixExpr.hpp"

#include "Stack.hpp"

long long odintsov::solvePostfixExpr(Queue< PostfixNode > expr)
{
  Stack< PostfixNode > solver;
  while (!expr.empty()) {
    const PostfixNode node = expr.head();
    expr.pop();
    if (node.isOperator()) {
      long long rhs = solver.tail().getOperand();
      solver.pop();
      long long lhs = solver.tail().getOperand();
      solver.pop();
      long long res = node.getOperator().exec(lhs, rhs);
      solver.push(PostfixNode(res));
    } else {
      solver.push(node);
    }
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
