#include "solveExpression.hpp"

#include "MathNode.hpp"
#include "Queue.hpp"
#include "StringSplitter.hpp"
#include "convertToPostfix.hpp"
#include "solvePostfix.hpp"

long long odintsov::solveExpression(const std::string& exprStr)
{
  Queue< MathNode > expr;
  StringSplitter exprSplit(exprStr);
  while (!exprSplit.empty()) {
    std::string element;
    exprSplit >> element;
    expr.push(MathNode(element));
  }
  expr = convertToPostfix(expr);
  return solvePostfix(expr);
}
